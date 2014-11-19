#include "../include/Octree.hpp"
#include <iostream>
#include <vector>

using namespace voxarium;

Octree::Octree(){
	for(int i=0; i<8; ++i) 
		children[i] = NULL;
	cubeType = 0;
}

Octree::Octree(int type){
	for(int i=0; i<8; ++i) 
		children[i] = NULL;
	cubeType = type;
}

Octree::Octree(Octree** newChildren){
	for(int i= 0; i < 8; ++i){
		children[i] = newChildren[i];
	}
	cubeType = 0;
}

char Octree::getCubeType(){
	return cubeType;
}

bool Octree::isLeaf(){
	for(int i = 0; i < 8; ++i){
		if(children[i] != NULL)
			return false;
	}
	return true;
}

void Octree::insert(char type){
	if(isLeaf())
		cubeType = type;
}

void Octree::insert(Octree &tree){
	for(int i= 0; i < 8; ++i){
		children[i] = tree.children[i];
	}
}

void Octree::getAllCoordinates(float taille, std::vector<float> centres){
	if(cubeType != 0){
		std::cout << "x : " << coo.x << " y : "<< coo.y << " z : " << coo.z << std::endl;
		centres.push_back(coo.x);
		centres.push_back(coo.y);
		centres.push_back(coo.z);
	}
	else{
		taille *= 0.5;
		for(int i = 0; i < 8; ++i){
			if(children[i] != NULL){
				children[i]->coo.x = coo.x + (((i&1)*2)-1)*taille;
				children[i]->coo.y = coo.y + (((i&10)*2)-1)*taille;
				children[i]->coo.z = coo.z + (((i&100)*2)-1)*taille;
				children[i]->getAllCoordinates(taille, centres);
			}
		}
	}
}