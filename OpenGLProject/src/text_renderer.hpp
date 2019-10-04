#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>
#include <map>


struct Character
{
    GLuint TextureID; // Texture ID of each glyph texture
    glm::ivec2 Size; // glyph Size
    glm::ivec2 Bearing; // baseline to left/top of glyph
    GLuint Advance; // id to next glyph
};

class TextRenderer
{
private:
    std::string text;
    GLfloat scale;
    glm::vec3 color;
    glm::vec2 position;

    GLuint vao, vbo, program;
    std::map<GLchar, Character> Characters;
public:
    TextRenderer(std::string text, std::string font, int size, glm::vec3 color, GLuint program);
    ~TextRenderer();

    void draw();
    inline void setPosition(glm::vec2 _position) { position = _position; }
    inline void setText(std::string _text) { text = _text; }
};

#endif