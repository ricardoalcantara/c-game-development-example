#include "text_renderer.hpp"
#include "log.hpp"

TextRenderer::TextRenderer(std::string text, std::string font, int size, glm::vec3 color, GLuint program)
{
    this->text = text;
    this->color = color;
    this->scale = 1.0;
    this->program = program;

    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
    glUseProgram(program);
    glUniformMatrix4fv(
        glGetUniformLocation(program, "projection"),
        1,
        GL_FALSE,
        glm::value_ptr(projection)
    );

    // FreeType
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        LOG_ERROR("ERROR::FREETYPE: Could not init FreeType Library");
    }

    //Load font
    FT_Face face;
    if (FT_New_Face(ft, font.c_str(), 0, &face))
    {
        LOG_ERROR("ERROR::FREETYPE: Failed to load font");
    }

    FT_Set_Pixel_Sizes(face, 0, size);

    // Disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (GLubyte i = 0; i < 128; i++)
    {
        if (FT_Load_Char(face, i, FT_LOAD_RENDER))
        {
            LOG_ERROR("ERROR::FREETYTPE: Failed to load Glyph");
            continue;
        }

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character = {
            texture,
            glm::ivec2(
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows
            ),
            glm::ivec2(
                face->glyph->bitmap_left,
                face->glyph->bitmap_top
            ),
            static_cast<GLuint>(face->glyph->advance.x)
        };

        Characters.insert(std::pair<GLchar, Character>(i, character));
    }
    
    glBindTexture(GL_TEXTURE_2D, 0);
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

TextRenderer::~TextRenderer()
{
}

void TextRenderer::draw()
{
    glm::vec2 textPos = this->position;

    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glUseProgram(program);
    glUniform3f(
        glGetUniformLocation(program, "textColor"),
        this->color.x,
        this->color.y,
        this->color.z
    );
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(vao);

    std::string::const_iterator c;

    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        GLfloat xpos = textPos.x + ch.Bearing.x * scale;
        GLfloat ypos = textPos.y - (ch.Size.y - ch.Bearing.y) * scale;

        GLfloat w = ch.Size.x * scale;
        GLfloat h = ch.Size.y * scale;

        GLfloat vertices[6][4] = {
            { xpos, ypos + h, 0.0, 0.0 },
            { xpos, ypos, 0.0, 1.0 },
            { xpos + w, ypos, 1.0, 1.0 },
            { xpos, ypos + h, 0.0, 0.0 },
            { xpos + w, ypos, 1.0, 1.0 },
            { xpos + w, ypos + h, 1.0, 0.0 },
        };

        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(
            GL_ARRAY_BUFFER,
            0,
            sizeof(vertices),
            vertices
        );
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(
            GL_TRIANGLES,
            0, 6
        );
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
        // 2^6 = 64
        //textPos.x += (ch.Advance / 64) * scale;
        textPos.x += (ch.Advance >> 6) * scale;
    }
    
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);

    glDisable(GL_BLEND);
}