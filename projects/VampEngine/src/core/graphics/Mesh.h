#ifndef VAPM_ENGINE_MESH_H
#define VAPM_ENGINE_MESH_H

/**
 *@file
*/

typedef struct VampVertexArray VampVertexArray;
typedef struct VampShader VampShader;

/**
 * The mesh structure.
*/
typedef struct VampMesh
{
    /**
     * Bind this mesh object in order to be drew by the next draw call.
     * 
     * @param[in] this The VampMesh object.
    */
    void (*Bind)(struct VampMesh *this);


    /**
     * Unbind this object.
     * 
     * @param[in] this The VampMesh object.
    */
    void (*UnBind)(struct VampMesh *this);



    VampVertexArray *__vao__; /**> @private*/
    VampShader *__shader__; /**> @private*/
}
VampMesh;


/**
 * Creates a new VampMesh object.
 * 
 * @param[in] vao The VampVertexArray object.
 * @param[in] shader The VampShader object.
 * 
 * @returns The newly created VampMesh object.
*/
VampMesh *VampNewMesh(VampVertexArray *vao, VampShader *shader);


/**
 * Destroys a VampMesh object.
 * It will also destroy every graphics object passed through the constructor
 * VampNewMesh()
 * 
 * @param[in] mesh The VampMesh object to be destroyed.
*/
void VampDestroyMesh(VampMesh *mesh);


#endif