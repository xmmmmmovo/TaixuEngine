#include "platform/opengl/ogl_context.hpp"

#include "ogl_context.hpp"


void taixu::OGLContext::initialize() {
    vertex_array = std::make_unique<OGLVertexArray>();
    
    //framebuffer  = std::make_unique<OGLFrameBuffer>();
    //framebuffer->allocate(size);
}

void taixu::OGLContext::bindMesh(Mesh mesh) const {
    vertex_array->bind();

    OGLElementBuffer element_buffer(mesh.indices, GL_STATIC_DRAW);

    std::vector<glm::vec3> vertices(mesh.vertices.size());
    for (std::size_t i = 0; i < mesh.vertices.size(); ++i) {
        vertices[i] = mesh.vertices[i].Position;
    }
    OGLVertexBuffer buf(vertices.size(), vertices.data(), GL_STATIC_DRAW, 3);
    vertex_array->addVBO(std::move(buf));
    vertex_array->setEBO(std::move(element_buffer));

    vertex_array->unbind();
}

void taixu::OGLContext::tickbyMesh(Mesh const&mesh) {
    framebuffer->bind();

    clear();

    vertex_array->bind();

    //Draw as meshes
    drawbyElement(mesh);

    vertex_array->unbind();

    framebuffer->unbind();
}

void taixu::OGLContext::drawbyElement(Mesh const& mesh) {
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(mesh.indices.size()),
                   GL_UNSIGNED_INT, 0);
}

void taixu::OGLContext::clear() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
