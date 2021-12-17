#ifndef OBJECT_CPP
#define OBJECT_CPP

#include <include/someSemblantOfAGameEngine/object.hpp>

Object::Object(Model& model){				Object::model	=&model;}

Object::Object(Model& model,const glm::mat4 modelMat){	Object::model	=&model;Object::modelMat=modelMat;}

#endif