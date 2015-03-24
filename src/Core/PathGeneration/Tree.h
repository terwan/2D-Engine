#pragma once

#include "../Core.h"
#include "../Math/Vector2D.h"

namespace ooe
{
	//Definition of node where each node has 0-1 parents and 0-* children
	struct Node {
		vec2 edge;
		vec2 vertex;
		std::shared_ptr<Node> parent;
		std::list<std::shared_ptr<Node>> children;

		Node(vec2 vert = vec2()) : vertex(vert) {}
	};


	//class implement Tree which contains a collection of nodes
	class Tree 
	{
	public:
		~Tree();
		Tree(){}

		//Find vertex in tree closest to x_rand
		std::shared_ptr<Node> nearestNeighbour(vec2 position) const;

		//Create a new node and place in tree
		void newNode(vec2 x_near, vec2 x_new);

		//Add new node to tree through a deep copy
		void addNode(std::shared_ptr<Node> node);

		//Retrieve the list of nodes
		const std::list<std::shared_ptr<Node>>& Nodes();

		//initialize tree
		void init(vec2 x_init);
	private:

		//delete every node in the tree
		void destroyTree();

		std::list<std::shared_ptr<Node>> nodes_;
	};

}