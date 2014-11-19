#include "../include/Chunk.hpp"
#include "../include/Octree.hpp"

using namespace voxarium;

Chunk::Chunk(){
	profondeur = 2;
	int etage = 0;
	root = Octree();
	genFlatFloor(root, etage);
}

void Chunk::genFlatFloor(Octree &subTree, int &etage){

	subTree.children[0] = NULL;
	subTree.children[1] = NULL;
	subTree.children[2] = new Octree();
	subTree.children[3] = new Octree();
	subTree.children[4] = NULL;
	subTree.children[5] = NULL;
	subTree.children[6] = new Octree();
	subTree.children[7] = new Octree();

	if(etage < profondeur-1){
		++etage;
		Chunk::genFlatFloor(*subTree.children[2], etage);
		Chunk::genFlatFloor(*subTree.children[3], etage);
		Chunk::genFlatFloor(*subTree.children[6], etage);
		Chunk::genFlatFloor(*subTree.children[7], etage);
	}
	else{
		subTree.children[2]->insert(1);
		subTree.children[3]->insert(1);
		subTree.children[6]->insert(1);
		subTree.children[7]->insert(1);
	}
}