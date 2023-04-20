#include "platform/opengl/ogl_context.hpp"

#include "ogl_context.hpp"


void taixu::OGLContext::initialize() {
    vertex_array = std::make_unique<OGLVertexArray>();
}

void taixu::OGLContext::bindMesh(Mesh mesh) const {
    vertex_array->bind();

    OGLElementBuffer element_buffer(mesh.indices, GL_STATIC_DRAW);
    //positions
    std::vector<glm::vec3> vertices(mesh.vertices.size());
    for (std::size_t i = 0; i < mesh.vertices.size(); ++i) {
        vertices[i] = mesh.vertices[i].Position;
    }
    OGLVertexBuffer vbuf(vertices.size(), vertices.data(), GL_STATIC_DRAW, 3);
    vertex_array->addVBO(std::move(vbuf));
    //normals
    std::vector<glm::vec3> normals(mesh.vertices.size());
    for (std::size_t i = 0; i < mesh.vertices.size(); ++i) {
        normals[i] = mesh.vertices[i].Normal;
    }
    OGLVertexBuffer nbuf(normals.size(), normals.data(), GL_STATIC_DRAW, 3);
    vertex_array->addVBO(std::move(nbuf));
    //textcoords
    std::vector<glm::vec2> textcoords(mesh.vertices.size());
    for (std::size_t i = 0; i < mesh.vertices.size(); ++i) {
        textcoords[i] = mesh.vertices[i].TexCoords;
    }
    OGLVertexBuffer tbuf(textcoords.size(), textcoords.data(), GL_STATIC_DRAW, 3);
    vertex_array->addVBO(std::move(tbuf));

    vertex_array->setEBO(std::move(element_buffer));
    
    vertex_array->unbind();



}

void taixu::OGLContext::tickMesh(Mesh const&mesh) {

    vertex_array->bind();
    
    //Draw as meshes
    drawbyElement(mesh);

    vertex_array->unbind();

}

void taixu::OGLContext::drawbyElement(Mesh const& mesh) {
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(mesh.indices.size()),
                   GL_UNSIGNED_INT, 0);
}

void taixu::OGLContext::clear() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
