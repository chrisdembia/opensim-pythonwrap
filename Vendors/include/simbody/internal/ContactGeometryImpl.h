#ifndef SimTK_SIMBODY_CONTACT_GEOMETRY_IMPL_H_
#define SimTK_SIMBODY_CONTACT_GEOMETRY_IMPL_H_

/* -------------------------------------------------------------------------- *
 *                      SimTK Core: SimTK Simbody(tm)                         *
 * -------------------------------------------------------------------------- *
 * This is part of the SimTK Core biosimulation toolkit originating from      *
 * Simbios, the NIH National Center for Physics-Based Simulation of           *
 * Biological Structures at Stanford, funded under the NIH Roadmap for        *
 * Medical Research, grant U54 GM072970. See https://simtk.org.               *
 *                                                                            *
 * Portions copyright (c) 2008-10 Stanford University and the Authors.        *
 * Authors: Peter Eastman                                                     *
 * Contributors: Michael Sherman                                              *
 *                                                                            *
 * Permission is hereby granted, free of charge, to any person obtaining a    *
 * copy of this software and associated documentation files (the "Software"), *
 * to deal in the Software without restriction, including without limitation  *
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,   *
 * and/or sell copies of the Software, and to permit persons to whom the      *
 * Software is furnished to do so, subject to the following conditions:       *
 *                                                                            *
 * The above copyright notice and this permission notice shall be included in *
 * all copies or substantial portions of the Software.                        *
 *                                                                            *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    *
 * THE AUTHORS, CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,    *
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR      *
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE  *
 * USE OR OTHER DEALINGS IN THE SOFTWARE.                                     *
 * -------------------------------------------------------------------------- */


#include "simbody/internal/ContactGeometry.h"

namespace SimTK {

//==============================================================================
//                             CONTACT GEOMETRY IMPL
//==============================================================================
class SimTK_SIMBODY_EXPORT ContactGeometryImpl {
public:
    ContactGeometryImpl(const std::string& type);
    virtual ~ContactGeometryImpl() {
        clearMyHandle();
    }
    const std::string& getType() const {
        return type;
    }
    int getTypeIndex() const {
        return typeIndex;
    }
    static int getIndexForType(std::string type);

    /* Create a new ContactGeometryTypeId and return this unique integer 
    (thread safe). Each distinct type of ContactGeometry should use this to
    initialize a static variable for that concrete class. */
    static ContactGeometryTypeId  createNewContactGeometryTypeId()
    {   static AtomicInteger nextAvailableId = 1;
        return ContactGeometryTypeId(nextAvailableId++); }

    virtual ContactGeometryTypeId getTypeId() const = 0;

    virtual ContactGeometryImpl* clone() const = 0;
    virtual Vec3 findNearestPoint(const Vec3& position, bool& inside, UnitVec3& normal) const = 0;
    virtual bool intersectsRay(const Vec3& origin, const UnitVec3& direction, Real& distance, UnitVec3& normal) const = 0;
    virtual void getBoundingSphere(Vec3& center, Real& radius) const = 0;
    ContactGeometry* getMyHandle() {
        return myHandle;
    }
    void setMyHandle(ContactGeometry& h) {
        myHandle = &h;
    }
    void clearMyHandle() {
        myHandle = 0;
    }
protected:
    ContactGeometry* myHandle;
    const std::string& type;
    int typeIndex;
};



//==============================================================================
//                             HALF SPACE IMPL
//==============================================================================
class ContactGeometry::HalfSpaceImpl : public ContactGeometryImpl {
public:
    HalfSpaceImpl() : ContactGeometryImpl(Type()) {
    }
    ContactGeometryImpl* clone() const {
        return new HalfSpaceImpl();
    }

    ContactGeometryTypeId getTypeId() const {return classTypeId();}
    static ContactGeometryTypeId classTypeId() {
        static const ContactGeometryTypeId id = 
            createNewContactGeometryTypeId();
        return id;
    }

    static const std::string& Type() {
        static std::string type = "halfspace";
        return type;
    }
    Vec3 findNearestPoint(const Vec3& position, bool& inside, UnitVec3& normal) const;
    bool intersectsRay(const Vec3& origin, const UnitVec3& direction, Real& distance, UnitVec3& normal) const;
    void getBoundingSphere(Vec3& center, Real& radius) const;
};



//==============================================================================
//                                SPHERE IMPL
//==============================================================================
class ContactGeometry::SphereImpl : public ContactGeometryImpl {
public:
    SphereImpl(Real radius) : ContactGeometryImpl(Type()), radius(radius) {
    }
    ContactGeometryImpl* clone() const {
        return new SphereImpl(radius);
    }
    Real getRadius() const {
        return radius;
    }
    void setRadius(Real r) {
        radius = r;
    }

    ContactGeometryTypeId getTypeId() const {return classTypeId();}
    static ContactGeometryTypeId classTypeId() {
        static const ContactGeometryTypeId id = 
            createNewContactGeometryTypeId();
        return id;
    }

    static const std::string& Type() {
        static std::string type = "sphere";
        return type;
    }
    Vec3 findNearestPoint(const Vec3& position, bool& inside, UnitVec3& normal) const;
    bool intersectsRay(const Vec3& origin, const UnitVec3& direction, Real& distance, UnitVec3& normal) const;
    void getBoundingSphere(Vec3& center, Real& radius) const;
private:
    Real radius;
};



//==============================================================================
//                            OBB TREE NODE IMPL
//==============================================================================
class OBBTreeNodeImpl {
public:
    OBBTreeNodeImpl() : child1(NULL), child2(NULL) {
    }
    OBBTreeNodeImpl(const OBBTreeNodeImpl& copy);
    ~OBBTreeNodeImpl();
    OrientedBoundingBox bounds;
    OBBTreeNodeImpl* child1;
    OBBTreeNodeImpl* child2;
    Array_<int> triangles;
    int numTriangles;
    Vec3 findNearestPoint(const ContactGeometry::TriangleMeshImpl& mesh, const Vec3& position, Real cutoff2, Real& distance2, int& face, Vec2& uv) const;
    bool intersectsRay(const ContactGeometry::TriangleMeshImpl& mesh, const Vec3& origin, const UnitVec3& direction, Real& distance, int& face, Vec2& uv) const;
};



//==============================================================================
//                            TRIANGLE MESH IMPL
//==============================================================================
class ContactGeometry::TriangleMeshImpl : public ContactGeometryImpl {
public:
    class Edge;
    class Face;
    class Vertex;

    TriangleMeshImpl(const ArrayViewConst_<Vec3>& vertexPositions, const ArrayViewConst_<int>& faceIndices, bool smooth);
    TriangleMeshImpl(const PolygonalMesh& mesh, bool smooth);
    ContactGeometryImpl* clone() const {
        return new TriangleMeshImpl(*this);
    }

    ContactGeometryTypeId getTypeId() const {return classTypeId();}
    static ContactGeometryTypeId classTypeId() {
        static const ContactGeometryTypeId id = 
            createNewContactGeometryTypeId();
        return id;
    }

    static const std::string& Type() {
        static std::string type = "triangle mesh";
        return type;
    }
    Vec3     findPoint(int face, const Vec2& uv) const;
    Vec3     findCentroid(int face) const;
    UnitVec3 findNormalAtPoint(int face, const Vec2& uv) const;
    Vec3 findNearestPoint(const Vec3& position, bool& inside, UnitVec3& normal) const;
    Vec3 findNearestPoint(const Vec3& position, bool& inside, int& face, Vec2& uv) const;
    Vec3 findNearestPointToFace(const Vec3& position, int face, Vec2& uv) const;
    bool intersectsRay(const Vec3& origin, const UnitVec3& direction, Real& distance, UnitVec3& normal) const;
    bool intersectsRay(const Vec3& origin, const UnitVec3& direction, Real& distance, int& face, Vec2& uv) const;
    void getBoundingSphere(Vec3& center, Real& radius) const;

    void createPolygonalMesh(PolygonalMesh& mesh) const;
private:
    void init(const Array_<Vec3>& vertexPositions, const Array_<int>& faceIndices);
    void createObbTree(OBBTreeNodeImpl& node, const Array_<int>& faceIndices);
    void splitObbAxis(const Array_<int>& parentIndices, Array_<int>& child1Indices, Array_<int>& child2Indices, int axis);
    void findBoundingSphere(Vec3* point[], int p, int b, Vec3& center, Real& radius);
    friend class ContactGeometry::TriangleMesh;
    friend class OBBTreeNodeImpl;

    Array_<Edge>    edges;
    Array_<Face>    faces;
    Array_<Vertex>  vertices;
    Vec3            boundingSphereCenter;
    Real            boundingSphereRadius;
    OBBTreeNodeImpl obb;
    bool            smooth;
};



//==============================================================================
//                          TriangleMeshImpl EDGE
//==============================================================================
class ContactGeometry::TriangleMeshImpl::Edge {
public:
    Edge(int vert1, int vert2, int face1, int face2) {
        vertices[0] = vert1;
        vertices[1] = vert2;
        faces[0] = face1;
        faces[1] = face2;
    }
    int     vertices[2];
    int     faces[2];
};



//==============================================================================
//                           TriangleMeshImpl FACE
//==============================================================================
class ContactGeometry::TriangleMeshImpl::Face {
public:
    Face(int vert1, int vert2, int vert3, 
         const Vec3& normal, Real area) 
    :   normal(normal), area(area) {
        vertices[0] = vert1;
        vertices[1] = vert2;
        vertices[2] = vert3;
    }
    int         vertices[3];
    int         edges[3];
    UnitVec3    normal;
    Real        area;
};



//==============================================================================
//                          TriangleMeshImpl VERTEX
//==============================================================================
class ContactGeometry::TriangleMeshImpl::Vertex {
public:
    Vertex(Vec3 pos) : pos(pos), firstEdge(-1) {
    }
    Vec3        pos;
    UnitVec3    normal;
    int         firstEdge;
};

} // namespace SimTK

#endif // SimTK_SIMBODY_CONTACT_GEOMETRY_IMPL_H_
