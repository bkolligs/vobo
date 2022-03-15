#ifndef _mesh_object_h_
#define _mesh_object_h_

namespace vobo
{
	

class MeshObject
{
private:
	/* data */
public:
	virtual void bind() = 0;
	virtual void loadShaders() = 0;
};

} // namespace vobo
#endif //_mesh_object_h_ header