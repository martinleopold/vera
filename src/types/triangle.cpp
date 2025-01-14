#include "vera/types/triangle.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/norm.hpp"
#include "glm/glm.hpp"

namespace vera {

Triangle::Triangle() { 
}

Triangle::Triangle(const glm::vec3 &_p0, const glm::vec3 &_p1, const glm::vec3 &_p2) {
    set(_p0,_p1, _p2);
}

Triangle::~Triangle() {
}

void Triangle::set(const glm::vec3 &_p0, const glm::vec3 &_p1, const glm::vec3 &_p2) {
    m_vertices[0] = _p0;
    m_vertices[1] = _p1;
    m_vertices[2] = _p2;
    m_normal = glm::cross(m_vertices[0] - m_vertices[2], m_vertices[1] - m_vertices[0]);
    m_area = glm::length( m_normal );
    m_normal = m_normal / m_area;
    // m_normal = glm::normalize( m_normal );
}

glm::vec3 Triangle::getBarycentricOf(const glm::vec3& _p) const {
    const glm::vec3 f0 = m_vertices[0] - _p;
    const glm::vec3 f1 = m_vertices[1] - _p;
    const glm::vec3 f2 = m_vertices[2] - _p;
    // calculate the areas and factors (order of parameters doesn't matter):
    // float a = glm::length(glm::cross(m_vertices[0] - m_vertices[1], m_vertices[0] - m_vertices[2])); // main triangle area a
    return glm::vec3(   glm::length(glm::cross(f1, f2)),        // p1's triangle area / a
                        glm::length(glm::cross(f2, f0)),        // p2's triangle area / a 
                        glm::length(glm::cross(f0, f1))) / m_area;   // p3's triangle area / a
}

// bool Triangle::containsPoint(const glm::vec3 &_p) const {
//     const glm::vec3 m_vertices[0] = m_vertices[2] - m_vertices[0];
//     const glm::vec3 m_vertices[1] = m_vertices[1] - m_vertices[0];
//     const glm::vec3 m_vertices[2] = _p - m_vertices[0];
    
//     // Compute dot products
//     float dot00 = glm::dot(m_vertices[0], m_vertices[0]);
//     float dot01 = glm::dot(m_vertices[0], m_vertices[1]);
//     float dot02 = glm::dot(m_vertices[0], m_vertices[2]);
//     float dot11 = glm::dot(m_vertices[1], m_vertices[1]);
//     float dot12 = glm::dot(m_vertices[1], m_vertices[2]);
    
//     // Compute barycentric coordinates
//     float invDenom = 1.0f / (dot00 * dot11 - dot01 * dot01);
//     float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
//     float v = (dot00 * dot12 - dot01 * dot02) * invDenom;
    
//     // Check if point is in triangle
//     return (u >= 0.0) && (v >= 0.0) && (u + v <= 1.0);
// }

void Triangle::setVertex(size_t _index, const glm::vec3& _vertex) {
    m_vertices[_index] = _vertex;
}

void Triangle::setColor(const glm::vec4 &_color) {
    if (m_colors.empty())
        m_colors.resize(3);

    std::fill(m_colors.begin(),m_colors.begin()+3, _color);
}

void Triangle::setColor(float _r, float _g, float _b, float _a) {
    setColor(glm::vec4(_r, _g, _b, _a));
}

void Triangle::setColor(size_t _index, const glm::vec4& _color) {
    if (m_colors.empty()) {
        m_colors.resize(3);
        std::fill(m_colors.begin(),m_colors.begin()+3, _color);
    }
    else
        m_colors[_index] = _color;
}

void Triangle::setNormal(size_t _index, const glm::vec3& _normal) {
        if (m_normals.empty()) {
        m_normals.resize(3);
        std::fill(m_normals.begin(),m_normals.begin()+3, _normal);
    }
    else
        m_normals[_index] = _normal;
}

void Triangle::setTexCoord(size_t _index, const glm::vec2& _texcoord) {
    if (m_texCoords.empty()) {
        m_texCoords.resize(3);
        std::fill(m_texCoords.begin(),m_texCoords.begin()+3, _texcoord);
    }
    else
        m_texCoords[_index] = _texcoord;
}

void Triangle::setTangent(size_t _index, const glm::vec4& _tangent) {
        if (m_tangents.empty()) {
        m_tangents.resize(3);
        std::fill(m_tangents.begin(), m_tangents.begin()+3, _tangent);
    }
    else
        m_tangents[_index] = _tangent;
}

void Triangle::setColors(const glm::vec4 &_p0, const glm::vec4 &_p1, const glm::vec4 &_p2) {
    m_colors.resize(3);
    m_colors[0] = _p0;
    m_colors[1] = _p1;
    m_colors[2] = _p2;
}

void Triangle::setNormals(const glm::vec3 &_p0, const glm::vec3 &_p1, const glm::vec3 &_p2) {
    m_normals.resize(3);
    m_normals[0] = _p0;
    m_normals[1] = _p1;
    m_normals[2] = _p2;
}

void Triangle::setTexCoords(const glm::vec2 &_p0, const glm::vec2 &_p1, const glm::vec2 &_p2) {
    m_texCoords.resize(3);
    m_texCoords[0] = _p0;
    m_texCoords[1] = _p1;
    m_texCoords[2] = _p2;
}

void Triangle::setTangents(const glm::vec4 &_p0, const glm::vec4 &_p1, const glm::vec4 &_p2) {
    m_tangents.resize(3);
    m_tangents[0] = _p0;
    m_tangents[1] = _p1;
    m_tangents[2] = _p2;
}

glm::vec3 Triangle::getVertex(const glm::vec3& _barycenter) const {
    return  getVertex(0) * _barycenter.x +
            getVertex(1) * _barycenter.y +
            getVertex(2) * _barycenter.z;
}

glm::vec4 Triangle::getColor(const glm::vec3& _barycenter) const {

    // if (material != nullptr) {
    //     if ( material->haveProperty("diffuse") ) {
    //         if (havem_TexCoords()) {
    //             glm::vec2 uv = getTexCoord(_barycenter);
    //             return material->getColor("diffuse", uv);
    //         }
    //         else
    //             return material->getColor("diffuse");
    //     }
    // }

    if (haveColors())
        return  getColor(0) * _barycenter.x +
                getColor(1) * _barycenter.y +
                getColor(2) * _barycenter.z;
    else
        return glm::vec4(1.0f);
}

glm::vec3 Triangle::getNormal(const glm::vec3& _barycenter) const {
    glm::vec3 n;
    if (haveNormals())
        n = getNormal(0) * _barycenter.x +
            getNormal(1) * _barycenter.y +
            getNormal(2) * _barycenter.z;
    else
        n = getNormal();

    // if (material != nullptr && havem_TexCoords() && haveTangents()) {
    //     if ( material->haveProperty("normalmap") ) {
    //         glm::vec2 uv = getTexCoord(_barycenter);
    //         glm::vec4 t = getTangent(_barycenter);
    //         glm::vec3 b = glm::cross( n, glm::vec3(t.x, t.y, t.z) ) * t.w;
    //         glm::mat3 tbn = glm::mat3( t, b, n );

    //         return tbn * ( material->getColor("normalmap", uv) * 2.0f - 1.0f);
    //     }
    // }

    return n;
}

glm::vec2 Triangle::getTexCoord(const glm::vec3& _barycenter) const {
    glm::vec2 uv =  getTexCoord(0) * _barycenter.x +
                    getTexCoord(1) * _barycenter.y +
                    getTexCoord(2) * _barycenter.z;
    
    uv.x = 1.0 - uv.x;

    return uv;
}

glm::vec4 Triangle::getTangent(const glm::vec3& _barycenter ) const {
    return  getTangent(0) * _barycenter.x +
            getTangent(1) * _barycenter.y +
            getTangent(2) * _barycenter.z;
}

// glm::vec3 Triangle::closest(const glm::vec3& _p) const {
//     // Project p onto the plane by stepping the distance from p to the plane
//     // in the direction opposite the normal: proj = p + n * dist
//     return _p - m_normal * signedDistance(_p);
// }

// size_t Triangle::closestCoorner(const glm::vec3& _p) const {
//     // Get 3 vectors, going from the test point to all potential candidates
//     glm::vec3 diff1 = _p - m_vertices[0]; // Vector from test point to potentially closest 1
//     glm::vec3 diff2 = _p - m_vertices[1]; // Vector from test point to potentially closest 2
//     glm::vec3 diff3 = _p - m_vertices[2]; // Vector from test point to potentially closest 3

//     // Find out how far away each point is using the difference
//     // vectors computed above
//     float distSq1 = glm::length2(diff1);  
//     float distSq2 = glm::length2(diff2);
//     float distSq3 = glm::length2(diff3);

//     // Find the shortest one
//     float min = std::min(distSq1, std::min(distSq2, distSq3));

//     // Finally, return the result
//     if (min == distSq1) 
//         return 0;
//     else if (min == distSq2)
//         return 1;
//     return  2;
// }

float Triangle::signedDistance(const glm::vec3& _p) const {
    glm::vec3 nearest;
    glm::vec3 normal;
    float distance;

    _closestPoint(_p, nearest, normal, distance);

    glm::vec3 u = _p - nearest;
    distance *= (glm::dot(u, normal) >= 0.0)? 1.0 : -1.0; 
    return distance;

    //    Then the *signed* distance from point p to the plane
    //    (in the direction of the normal) is:  dist = p . n - v . n
    // return glm::dot(_p, m_normal) - glm::dot(m_vertices[0], m_normal);
}

void Triangle::_closestPoint(const glm::vec3& _point, glm::vec3& _nearest_point, glm::vec3& _pseudonormal, float& _squareDistance) const {
    glm::vec3 diff = m_vertices[0] - _point;
    glm::vec3 edge0 = m_vertices[1] - m_vertices[0];
    glm::vec3 edge1 = m_vertices[2] - m_vertices[0];
    _pseudonormal = getNormal();

    float a00 = glm::dot(edge0, edge0);
    float a01 = glm::dot(edge0, edge1);
    float a11 = glm::dot(edge1, edge1);
    float b0 = glm::dot(diff, edge0);
    float b1 = glm::dot(diff, edge1);
    float c = glm::dot(diff, diff);
    float det = std::abs(a00 * a11 - a01 * a01);
    float s = a01 * b1 - a11 * b0;
    float t = a01 * b0 - a00 * b1;
    _squareDistance = -1.0;

    if (s + t <= det) {
        if (s < 0) {
            // region 4
            if (t < 0) {
                if (b0 < 0) {
                    t = 0;
                    if (-b0 >= a00) {
                        _pseudonormal = getNormal(1);
                        s = 1;
                        _squareDistance = a00 + (2) * b0 + c;
                    }
                    else {
                        // nearest_entity = NearestEntity::E01;
                        s = -b0 / a00;
                        _squareDistance = b0 * s + c;
                    }
                }
                else {
                    s = 0;
                    if (b1 >= 0) {
                        _pseudonormal = getNormal(0);
                        t = 0;
                        _squareDistance = c;
                    }
                    else if (-b1 >= a11) {
                        _pseudonormal = getNormal(2);
                        t = 1;
                        _squareDistance = a11 + (2) * b1 + c;
                    }
                    else {
                        // nearest_entity = NearestEntity::E02;
                        t = -b1 / a11;
                        _squareDistance = b1 * t + c;
                    }
                }
            }
            // region 3
            else {
                s = 0;
                if (b1 >= 0) {
                    _pseudonormal = getNormal(0);
                    t = 0;
                    _squareDistance = c;
                }
                else if (-b1 >= a11) {
                    _pseudonormal = getNormal(2);
                    t = 1;
                    _squareDistance = a11 + (2) * b1 + c;
                }
                else {
                    // nearest_entity = NearestEntity::E02;
                    t = -b1 / a11;
                    _squareDistance = b1 * t + c;
                }
            }
        }
        // region 5
        else if (t < 0) {
            t = 0;
            if (b0 >= 0) {
                _pseudonormal = getNormal(0);
                s = 0;
                _squareDistance = c;
            }
            else if (-b0 >= a00) {
                _pseudonormal = getNormal(1);
                s = 1;
                _squareDistance = a00 + (2) * b0 + c;
            }
            else {
                // nearest_entity = NearestEntity::E01;
                s = -b0 / a00;
                _squareDistance = b0 * s + c;
            }
        }
        // region 0
        else {
            // nearest_entity = NearestEntity::F;
            // minimum at interior point
            float invDet = (1) / det;
            s *= invDet;
            t *= invDet;
            _squareDistance = s * (a00 * s + a01 * t + (2) * b0) +
                t * (a01 * s + a11 * t + (2) * b1) + c;
        }
    }
    else {
        float tmp0, tmp1, numer, denom;
        // region 2
        if (s < 0) {
            tmp0 = a01 + b0;
            tmp1 = a11 + b1;
            if (tmp1 > tmp0) {
                numer = tmp1 - tmp0;
                denom = a00 - (2) * a01 + a11;
                if (numer >= denom) {
                    _pseudonormal = getNormal(1);
                    s = 1;
                    t = 0;
                    _squareDistance = a00 + (2) * b0 + c;
                }
                else {
                    s = numer / denom;
                    t = 1 - s;
                    _squareDistance = s * (a00 * s + a01 * t + (2) * b0) +
                        t * (a01 * s + a11 * t + (2) * b1) + c;
                }
            }
            else {
                s = 0;
                if (tmp1 <= 0) {
                    _pseudonormal = getNormal(2);
                    t = 1;
                    _squareDistance = a11 + (2) * b1 + c;
                }
                else if (b1 >= 0) {
                    _pseudonormal = getNormal(0);
                    t = 0;
                    _squareDistance = c;
                }
                else {
                    // nearest_entity = NearestEntity::E02;
                    t = -b1 / a11;
                    _squareDistance = b1 * t + c;
                }
            }
        }
        // region 6
        else if (t < 0) {
            tmp0 = a01 + b1;
            tmp1 = a00 + b0;
            if (tmp1 > tmp0) {
                numer = tmp1 - tmp0;
                denom = a00 - (2) * a01 + a11;
                if (numer >= denom) {
                    _pseudonormal = getNormal(2);
                    t = 1;
                    s = 0;
                    _squareDistance = a11 + (2) * b1 + c;
                }
                else {
                    // nearest_entity = NearestEntity::E12;
                    t = numer / denom;
                    s = 1 - t;
                    _squareDistance = s * (a00 * s + a01 * t + (2) * b0) +
                        t * (a01 * s + a11 * t + (2) * b1) + c;
                }
            }
            else {
                t = 0;
                if (tmp1 <= 0) {
                    _pseudonormal = getNormal(1);
                    s = 1;
                    _squareDistance = a00 + (2) * b0 + c;
                }
                else if (b0 >= 0) {
                    _pseudonormal = getNormal(0);
                    s = 0;
                    _squareDistance = c;
                }
                else {
                    // nearest_entity = NearestEntity::E01;
                    s = -b0 / a00;
                    _squareDistance = b0 * s + c;
                }
            }
        }
        // region 1
        else {
            numer = a11 + b1 - a01 - b0;
            if (numer <= 0) {
                // nearest_entity = NearestEntity::m_vertices[2];
                _pseudonormal = getNormal(2);
                s = 0;
                t = 1;
                _squareDistance = a11 + (2) * b1 + c;
            }
            else {
                denom = a00 - (2) * a01 + a11;
                if (numer >= denom) {
                    // nearest_entity = NearestEntity::m_vertices[1];
                    _pseudonormal = getNormal(1);
                    s = 1;
                    t = 0;
                    _squareDistance = a00 + (2) * b0 + c;
                }
                else {
                    // nearest_entity = NearestEntity::E12;
                    s = numer / denom;
                    t = 1 - s;
                    _squareDistance = s * (a00 * s + a01 * t + (2) * b0) +
                        t * (a01 * s + a11 * t + (2) * b1) + c;
                }
            }
        }
    }

    // Account for numerical round-off error.
    if (_squareDistance < 0)
        _squareDistance = 0;

    _nearest_point = m_vertices[0] + s * edge0 + t * edge1;
}


}