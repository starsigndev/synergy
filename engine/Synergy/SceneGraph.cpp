#include "SceneGraph.h"
#include "Node3D.h"
#include "StringHelper.h"
#include "Camera.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/intersect.hpp"
#include "Entity.h"
#include "Mesh.h"
#include "PhysicsWorld.h"


int graph_index = 0;

SceneGraph::SceneGraph() {

	graph_index++;
	_Name = StringHelper::AddToString("SceneGraph", graph_index);
	_RootNode = new Node3D;
    _RootNode->SetName("Graph Root");
    _Physics = new PhysicsWorld;

}

void SceneGraph::AddNode(Node3D* node) {

	_RootNode->AddNode(node);

}

Node3D* SceneGraph::GetRootNode() {

	return _RootNode;

}

void SceneGraph::Update(float dt) {

	UpdateNode(_RootNode,dt);

}

void SceneGraph::UpdateNode(Node3D* node, float dt)
{

	node->UpdateNode(dt);

	for (auto const& sub : node->GetChildren()) {

		UpdateNode(sub, dt);

	}

}


CastHit SceneGraph::MouseRaycast(glm::vec2 mousePos, Camera* camera, float width, float height,Entity* entity) {




    // these positions must be in range [-1, 1] (!!!), not [0, width] and [0, height]
    float mouseX = mousePos.x / (width * 0.5f) - 1.0f;
    float mouseY = mousePos.y / (height * 0.5f) - 1.0f;

    glm::mat4 proj = camera->GetProjectionMatrix();
    glm::mat4 view = glm::inverse(camera->GetRotation());//   glm::lookAt(glm::vec3(0.0f), CameraDirection, CameraUpVector);


    glm::mat4 invVP = glm::inverse(proj * view);
    glm::vec4 screenPos = glm::vec4(mouseX, -mouseY, 1.0f, 1.0f);
    glm::vec4 worldPos = invVP * screenPos;

    glm::vec3 dir = glm::normalize(glm::vec3(worldPos));

    glm::vec3 start = glm::unProject(glm::vec3(mousePos.x, height - mousePos.y, 0), camera->GetWorldMatrix(), camera->GetProjectionMatrix(), glm::ivec4(0, 0, width, height));
    glm::vec3 end = glm::unProject(glm::vec3(mousePos.x, height - mousePos.y, 1.0), camera->GetWorldMatrix(), camera->GetProjectionMatrix(), glm::ivec4(0, 0, width, height));

    glm::vec3 rdir = end - start;

    rdir = glm::normalize(rdir);

    std::cout << "Start: " << " X: " << rdir.x << " Y: " << rdir.y << " Z: " << rdir.z << std::endl;

    // Now you can use the ray start and end in world space for ray casting
    return Raycast(camera->GetPosition(), rdir, entity->GetMeshes());

}

CastHit SceneGraph::MouseRaycast(glm::vec2 mousePos,Camera* camera,float width,float height) {


    

    // these positions must be in range [-1, 1] (!!!), not [0, width] and [0, height]
    float mouseX = mousePos.x / (width * 0.5f) - 1.0f;
    float mouseY = mousePos.y / (height * 0.5f) - 1.0f;

    glm::mat4 proj = camera->GetProjectionMatrix();
    glm::mat4 view =glm::inverse(camera->GetRotation());//   glm::lookAt(glm::vec3(0.0f), CameraDirection, CameraUpVector);


    glm::mat4 invVP = glm::inverse(proj * view);
    glm::vec4 screenPos = glm::vec4(mouseX, -mouseY, 1.0f, 1.0f);
    glm::vec4 worldPos = invVP * screenPos;

    glm::vec3 dir = glm::normalize(glm::vec3(worldPos));

    glm::vec3 start = glm::unProject(glm::vec3(mousePos.x, height-mousePos.y,0),camera->GetWorldMatrix(),camera->GetProjectionMatrix(),glm::ivec4(0,0,width,height));
    glm::vec3 end = glm::unProject(glm::vec3(mousePos.x, height-mousePos.y,1.0), camera->GetWorldMatrix(), camera->GetProjectionMatrix(), glm::ivec4(0, 0, width, height));

    glm::vec3 rdir = end - start;

    rdir = glm::normalize(rdir);

    std::cout << "Start: " << " X: " << rdir.x << " Y: "<<rdir.y << " Z: " << rdir.z << std::endl;

    // Now you can use the ray start and end in world space for ray casting
    return Raycast(camera->GetPosition(), rdir);

}
const float EPSILON = 0.0000001f;
bool rayTriangleIntersect(const glm::vec3& rayStart, const glm::vec3& rayEnd,
    const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, CastHit& hitResult) {

    
    hitResult.hit = false;

    /*
    bool RayIntersectsTriangle(Vector3D rayOrigin,
        Vector3D rayVector,
        Triangle * inTriangle,
        Vector3D & outIntersectionPoint)
    */






    glm::vec3 edge1 =v1 - v0;// vertex1 - vertex0;
    glm::vec3 edge2 = v2 - v0;

    glm::vec3 h = glm::cross(rayEnd, edge2);
    float a = glm::dot(edge1, h);
    if (a > -EPSILON && a < EPSILON)
        return false;    // This ray is parallel to this triangle.
    float f = 1.0f / a;
    glm::vec3 s = rayStart - v0;
    float u = f * glm::dot(s, h);
    if (u < 0.0f || u > 1.0f)
        return false;
    glm::vec3 q = glm::cross(s, edge1);
    float v = f * glm::dot(rayEnd, q);
    if (v < 0.0f || u + v > 1.0f)
        return false;
    // At this stage we can compute t to find out where the intersection point is on the line.
    float t = f * glm::dot(edge2, q);

    if (t > EPSILON) // ray intersection
    {
        //outIntersectionPoint = rayOrigin + rayVector * t;
        hitResult.hit = true;
        hitResult.position = rayStart + rayEnd * t;
        hitResult.distance = t;
        return true;
    }
    else // This means that there is a line intersection but not a ray intersection.
        return false;

    return false;
}

CastHit SceneGraph::Raycast(glm::vec3 pos, glm::vec3 dir, std::vector<Mesh*> meshes) {

    CastHit small_hit;

    small_hit.hit = false;

    float small_dist = 0.0f;
    bool first_hit = true;


    for (auto const& mesh : meshes) {

        auto vertices = mesh->GetVertices();
        auto world_mat = mesh->GetOwner()->GetWorldMatrix();
        for (auto const& tri : mesh->GetTriangles())
        {

            auto p0 = glm::vec3(world_mat * glm::vec4(vertices[tri.V0].position, 1.0));
            auto p1 = glm::vec3(world_mat * glm::vec4(vertices[tri.V1].position, 1.0));
            auto p2 = glm::vec3(world_mat * glm::vec4(vertices[tri.V2].position, 1.0));

            CastHit hitResult;

            float dist = 0;
            glm::vec2 bb;

            if (rayTriangleIntersect(pos, dir, p0, p1, p2, hitResult))
            {
                if (hitResult.distance < 0) continue;
                if (first_hit) {

                    hitResult.mesh = mesh;
                    hitResult.entity = mesh->GetOwner();
                    small_dist = hitResult.distance;
                    small_hit = hitResult;

                    // small_hit.distance = dist;
                    small_hit.hit = true;
                    first_hit = false;


                }
                else {

                    if (dist < small_dist) {

                        hitResult.mesh = mesh;
                        hitResult.entity = mesh->GetOwner();
                        small_dist = hitResult.distance;
                        small_hit = hitResult;
                        //small_hit.distance = dist;
                        small_hit.hit = true;



                    }

                }

            }

        }

    }

    return small_hit;


}
CastHit SceneGraph::Raycast(glm::vec3 pos, glm::vec3 dir) {

    CastHit small_hit;

    small_hit.hit = false;

    float small_dist = 0.0f;
    bool first_hit = true;

    auto meshes = GetMeshes();

    for (auto const& mesh : meshes) {

        auto vertices = mesh->GetVertices();

        auto world_mat = mesh->GetOwner()->GetWorldMatrix();

        for (auto const& tri : mesh->GetTriangles())
        {

            auto p0 = glm::vec3(world_mat*glm::vec4(vertices[tri.V0].position, 1.0));
            auto p1 = glm::vec3(world_mat*glm::vec4(vertices[tri.V1].position, 1.0));
            auto p2 = glm::vec3(world_mat*glm::vec4(vertices[tri.V2].position, 1.0));
            CastHit hitResult;

            float dist = 0;
            glm::vec2 bb;

            if (rayTriangleIntersect(pos,dir, p0, p1, p2, hitResult))
            {
                if (hitResult.distance < 0) continue;
                if (first_hit) {

                    hitResult.mesh = mesh;
                    hitResult.entity = mesh->GetOwner();
                    hitResult.node = (Node3D*)hitResult.entity;
                    small_dist = hitResult.distance;
                    small_hit = hitResult;
                    
                   // small_hit.distance = dist;
                    small_hit.hit = true;
                    first_hit = false;


                }
                else {

                    if (dist < small_dist) {

                        hitResult.mesh = mesh;
                        hitResult.entity = mesh->GetOwner();
                        hitResult.node = (Node3D*)hitResult.entity;
                        small_dist = hitResult.distance;
                        small_hit = hitResult;
                        //small_hit.distance = dist;
                        small_hit.hit = true;



                    }

                }

            }

        }

    }

    return small_hit;

}

std::vector<Mesh*> SceneGraph::GetMeshes() {

    std::vector<Mesh*> meshes;

    return GetMeshes(meshes,_RootNode);

}

std::vector<Mesh*> SceneGraph::GetMeshes(std::vector<Mesh*> meshes,Node3D* node)
{

    Entity* entityPtr = dynamic_cast<Entity*>(node);
    if (entityPtr)
    {
        //meshes.push_back(entityPtr);
        for (auto const& mesh : entityPtr->GetMeshes()) {

            meshes.push_back(mesh);

        }

    }

    for (auto const& sub : node->GetChildren()) {

        meshes = GetMeshes(meshes, sub);

    }

    return meshes;

}

void SceneGraph::BeginPlay() {

    BeginNode(_RootNode);

}

void SceneGraph::BeginNode(Node3D* node) {


    node->BeginPlay();

    for (auto const& sub : node->GetNodes()) {
        BeginNode(sub);
    }

}

void SceneGraph::UpdatePlay(float dt) {

    PhysicsWorld::This->UpdateWorld(dt);
    UpdateNode(_RootNode,dt);

}



void SceneGraph::StopPlay() {

    StopNode(_RootNode);

}

void SceneGraph::StopNode(Node3D* node) {

    node->StopPlay();

    for (auto const& sub : node->GetNodes()) {
        StopNode(sub);
    }

}


void SceneGraph::PausePlay() {



}