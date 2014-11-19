#pragma once

#include "Point3D.hpp"
#include <vector>

namespace voxarium{
	class Octree{
		private :

		char cubeType;
		

		public :

		Octree *children[8];
		Point3D coo;

		Octree();
		Octree(int type);
		Octree(Octree** newChildren);

		char getCubeType();

		bool isLeaf();
		void insert(char type);
		void insert(Octree &tree);
		void getAllCoordinates(float taille, std::vector<float> vertices);
	};
}