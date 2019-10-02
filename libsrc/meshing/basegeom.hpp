#ifndef FILE_BASEGEOM
#define FILE_BASEGEOM

/**************************************************************************/
/* File:   basegeom.hpp                                                   */
/* Author: Joachim Schoeberl                                              */
/* Date:   23. Aug. 09                                                    */
/**************************************************************************/


struct Tcl_Interp;

namespace netgen
{

  class DLL_HEADER NetgenGeometry
  {
  public:
    virtual ~NetgenGeometry () { ; }

    virtual int GenerateMesh (shared_ptr<Mesh> & mesh, MeshingParameters & mparam);

    virtual const Refinement & GetRefinement () const;

    virtual void DoArchive(Archive&)
  { throw NgException("DoArchive not implemented for " + Demangle(typeid(*this).name())); }

    virtual Mesh::GEOM_TYPE GetGeomType() const { return Mesh::NO_GEOM; }
    virtual void Analyse(Mesh& mesh,
                         const MeshingParameters& mparam) {}
    virtual void FindEdges(Mesh& mesh, const MeshingParameters& mparam) {}
    virtual void MeshSurface(Mesh& mesh, const MeshingParameters& mparam) {}
    virtual void OptimizeSurface(Mesh& mesh, const MeshingParameters& mparam) {}
    virtual void FinalizeMesh(Mesh& mesh) const {}
    virtual void Save (string filename) const;
    virtual void SaveToMeshFile (ostream & /* ost */) const { ; }
  };





  class DLL_HEADER GeometryRegister
  {
  public:
    virtual ~GeometryRegister();
    virtual NetgenGeometry * Load (string filename) const = 0;
    virtual NetgenGeometry * LoadFromMeshFile (istream & /* ist */) const { return NULL; }
    virtual class VisualScene * GetVisualScene (const NetgenGeometry * /* geom */) const
    { return NULL; }
    virtual void SetParameters (Tcl_Interp * /* interp */) { ; }
  };

  class DLL_HEADER GeometryRegisterArray : public NgArray<GeometryRegister*>
  {
  public:
    virtual ~GeometryRegisterArray()
    {
      for (int i = 0; i < Size(); i++)
        delete (*this)[i];
    }

    virtual shared_ptr<NetgenGeometry> LoadFromMeshFile (istream & ist) const;
  };

  // extern DLL_HEADER NgArray<GeometryRegister*> geometryregister; 
  extern DLL_HEADER GeometryRegisterArray geometryregister; 
}



#endif
