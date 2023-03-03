#include"platform/opengl/OGLContext.hpp"
#include "OGLContext.hpp"


void taixu::OGLContext::initialize() 
{
    vertex_arry = std::make_unique<OGLVertexArray>();
    framebuffer = std::make_unique<OGLFrameBuffer>();
    framebuffer->allocate(size);
}

void taixu::OGLContext::bindMesh(Mesh mesh) 
{

        //glBindVertexArray(vertex_arry_object);
        vertex_arry->bind();
        
        // glGenBuffers(1, &vertex_buffer_id);
        // // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        // //Bind vertices data of mesh
        // glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
        //glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex),
        //              &mesh.vertices[0], GL_DYNAMIC_DRAW);
        OGLVertexBuffer vertex_buffer;
        //vertex_arry->setVBO(vertex_buffer);
        vertex_buffer.bind();
        vertex_buffer.setData(mesh.vertices.size() * sizeof(Vertex),
                              &mesh.vertices[0]);

        // glGenBuffers(1, &element_buffer_id);
        // //Bind indices data of mesh
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_id);
        // glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        //              mesh.indices.size() * sizeof(unsigned int),
        //              &mesh.indices[0], GL_DYNAMIC_DRAW);
        OGLElementBuffer element_buffer(mesh.indices);

        // vertex Positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              (void *) 0);
        // vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              (void *) offsetof(Vertex, Normal));
        // vertex texture coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              (void *) offsetof(Vertex, TexCoords));
        // vertex tangent
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              (void *) offsetof(Vertex, Tangent));
        // vertex bitangent
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              (void *) offsetof(Vertex, Bitangent));
        // ids
        glEnableVertexAttribArray(5);
        glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex),
                               (void *) offsetof(Vertex, m_BoneIDs));
        // weights
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              (void *) offsetof(Vertex, m_Weights));
        //glBindVertexArray(0);
        vertex_arry->unbind();
}

void taixu::OGLContext::tickbyMesh(Mesh mesh) 
{
    //glBindFramebuffer(GL_FRAMEBUFFER, bufferTexId);
    framebuffer->bind();
    //glBufferData(GL_FRAMEBUFFER,_id);
    
    clear();

    // glBindVertexArray(
    //         VAO);
    vertex_arry->bind();
    
    //Draw as meshes
    drawbyElement(mesh);

    //glBindFramebuffer(GL_FRAMEBUFFER, 0);
    framebuffer->unbind(); 
}

void taixu::OGLContext::drawbyElement(Mesh mesh) 
{
    glDrawElements(GL_TRIANGLES,
                   static_cast<unsigned int>(mesh.indices.size()),
                   GL_UNSIGNED_INT, 0);
}

void taixu::OGLContext::clear() 
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
