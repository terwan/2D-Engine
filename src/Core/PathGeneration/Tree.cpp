#include "Tree.h"

namespace ooe
{
	Tree::~Tree()
	{
		destroyTree();
	}

	void Tree::addNode(std::shared_ptr<Node> node)
	{
		if (node == nullptr) return;

		auto new_node = std::shared_ptr<Node>(new Node);
		new_node->children = node->children;
		new_node->edge = node->edge;
		new_node->parent = node->parent;
		new_node->vertex = node->vertex;

		nodes_.push_back(new_node);
	}


	std::shared_ptr<Node> Tree::nearestNeighbour(vec2 position) const
	{
		//Return if empty tree
		if (nodes_.empty()) return nullptr;

		std::shared_ptr<Node> nearest;
		nearest = nodes_.front();

		//if distance between position and a vertex in tree is less than distance
		//between position and it's current nearest neighbour
		//nearest = vert
		for (auto node : nodes_) {
			if (position.distance(node->vertex) < position.distance(nearest->vertex)) {
				nearest = node;
			}
		}
		return nearest;
	}


	void Tree::newNode(vec2 x_near, vec2 x_new)
	{
		//algorithm requires at least 1 node in tree
		if (nodes_.empty()) return;

		std::shared_ptr<Node> new_node = std::shared_ptr<Node>(new Node());

		//set Parent of new node and add new node as child of that parent
		for (auto tree_node : nodes_) {
			if (x_near == tree_node->vertex) {
				new_node->parent = tree_node;
				tree_node->children.push_back(new_node);
				break;
			}
		}

		//Set vertex data of this new node
		new_node->vertex = x_new;

		//Compute edge size
		new_node->edge = new_node->vertex - new_node->parent->vertex;

		//Add new node to tree
		nodes_.push_back(new_node);
	}


	const std::list<std::shared_ptr<Node>>& Tree::Nodes()
	{
		return nodes_;
	}


	void Tree::destroyTree()
	{
		//for (auto t : nodes_) delete t;
	}


	void Tree::init(vec2 x_init)
	{
		//cleanup non-empty trees
		if (!nodes_.empty()) destroyTree();

		//init Tree with a root node
		std::shared_ptr<Node> n = std::shared_ptr<Node>(new Node);
		n->vertex = x_init;
		nodes_.push_back(n);
	}
}