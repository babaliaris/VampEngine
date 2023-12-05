#ifndef VAMP_ENGINE_SHADER_H
#define VAMP_ENGINE_SHADER_H

/**
 * @file
*/

typedef char * sds;

/**
 * The shader structure.
*/
typedef struct VampShader
{
    /**
     * Binds this shader object.
     * 
     * @param[in] this The shader object.
    */
    void (*Bind)(struct VampShader *this);

    /**
     * UnBinds this shader object.
     * 
     * @param[in] this The shader object.
    */
    void (*Unbind)(struct VampShader *this);


    /**
     * Get the vertex shader path filename.
     * 
     * @param[in] this The shader object.
    */
    const char *(*GetVertexPath)(struct VampShader *this);


    /**
     * Get the fragment shader path filename.
     * 
     * @param[in] this The shader object.
    */
    const char *(*GetFragmentPath)(struct VampShader *this);

    void *__child__; /**< @private*/
    void (*__ChildDeconstructor__)(void *child); /**< @private*/
    sds __vertex_path__; /**< @private*/
    sds __fragment_path__; /**< @private*/

}
VampShader;


/**
 * Creates the implementation depending on the operating system.
 * 
 * @return The newly created VampShader object.
*/
VampShader *VampCreateShader(const char *vertex_path, const char *fragment_path);


/**
 * Destroys the VampShader object.
 * 
 * @param[in] shader The VampShader to be destroyed.
*/
void VampDestroyShader(VampShader *shader);

/**
 * @private
*/
VampShader *__VampNewShader__(const char *vertex_path, const char *fragment_path);

#endif