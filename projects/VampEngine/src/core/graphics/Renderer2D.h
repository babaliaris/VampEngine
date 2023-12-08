#ifndef VAMP_ENGINE_RENDERER_2D_H
#define VAMP_ENGINE_RENDERER_2D_H

typedef struct VampList VampList;
typedef struct VampVertexArray VampVertexArray;
typedef struct VampShader VampShader;

/**
 * @file
*/


typedef struct VampMesh VampMesh;


/**
 * The renderer2D structure.
*/
typedef struct VampRenderer2D
{
    /**
     * Push draw data to the renderer list. Upon destruction,
     * VampVertexArray and VampShader will be destroyed as well.
     * 
     * @param[in] this The VampRenderer2D object.
     * @param[in] mesh The VampMesh object.
    */
    void (*PushDrawData)(struct VampRenderer2D *this, VampMesh *mesh);


    /**
     * Draw a single mesh object.
     * 
     * @param[in] this The VampRenderer2D object.
     * @param[in] mesh The VampMesh object.
    */
    void (*DrawArrays)(struct VampRenderer2D *this, VampMesh *mesh);


    /**
     * Draw all the meshes VampRendererData2D that have been pushed into this renderer.
     * 
     * @param[in] this The VampRenderer2D object.
    */
    void (*DrawAllArrays)(struct VampRenderer2D *this);



    VampList *__list__; /**< @private*/
    void *__child__; /**< @private*/
    void (*__ChildDeconstructor__)(void *child); /**< @private*/
}
VampRenderer2D;



/**
 * Create a new VampCreateRenderer2D implementation based on the operating system.
 * @returns The newly created VampCreateRenderer2D object.
*/
VampRenderer2D *VampCreateRenderer2D();


/**
 * Destroy the VampCreateRenderer2D object.
 * 
 * @param[in] renderer2D The VampCreateRenderer2D object to be destroyed.
*/
void VampDestroyRenderer2D(VampRenderer2D *renderer2D);



/**
 * Create a new VampCreateRenderer2D object.
 * @private
 * @returns The newly created VampCreateRenderer2D object.
*/
VampRenderer2D *__VampNewRenderer2D__();

#endif