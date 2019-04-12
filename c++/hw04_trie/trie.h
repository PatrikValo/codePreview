#ifndef TRIE_H
#define TRIE_H
#pragma once

#include <array>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

template <typename Alphabet, typename Value>
class Trie {
public:
	using ItemList = std::vector<std::pair<std::string, const Value&>>;

	class Node {
		friend class Trie;
		std::unique_ptr<Value> value_;
		std::unique_ptr<Node> succs_[Alphabet::size];
		int succ_count_ = 0;
		Node* parent_ = nullptr;

	public:
		Node() = default;

		Node(Node* parent)
		    : parent_(parent) {
		}

		const Node* child(char letter) const {
			int succ = Alphabet::ord(letter);
			if (succ == -1) {
				throw std::out_of_range("Out of range Alphabet");
			}
			return succs_[succ].get();
		}

		const Node* parent() const {
			return parent_;
		}

		const Value* value() const {
			return value_.get();
		}
	};

private:
	// root of trie
	Node root_;

	template <typename T, typename Self>
	T find(Self& /*self*/, T node, const std::string& key) const {
		for (char ch : key) {
			if (node->child(ch) != nullptr) {
				node = node->succs_[Alphabet::ord(ch)].get();
			} else {
				return nullptr;
			}
		}

		return node;
	}

	Value* insert_n(Node* node, const std::string& key, size_t index, const Value& value, bool& insert) {
		if (index == key.size()) {
			if (node->value() != nullptr) {
				return node->value_.get();
			}
			insert = true;
			node->value_ = std::make_unique<Value>(value);
			return node->value_.get();
		}

		if (node->child(key[index]) == nullptr) {
			node->succs_[Alphabet::ord(key[index])] = std::make_unique<Node>(node);
			node->succ_count_++;
		}

		return insert_n(node->succs_[Alphabet::ord(key[index])].get(), key, index + 1, value, insert);
	}

	void items_n(ItemList& itemList, const Node* node, const std::string& key) const {
		if (node == nullptr) {
			return;
		}

		if (node->value() != nullptr) {
			itemList.emplace_back(key, *node->value_);
		}

		for (int i = 0; i < Alphabet::size; i++) {
			if (node->child(Alphabet::chr(i)) != nullptr) {
				items_n(itemList, node->succs_[i].get(), key + Alphabet::chr(i));
			}
		}
	}

	char draw_n(std::ostream& output, const Node* node, char name) const {
		if (node == nullptr) {
			return name;
		}

		// node info
		char nameOfNode = name;
		output << "\t" << '\"' << nameOfNode << '\"' << " [label=\"";
		if (node->value() != nullptr) {
			output << *node->value();
		}
		output << "\"]\n";

		for (int i = 0; i < Alphabet::size; i++) {
			if (node->child(Alphabet::chr(i)) != nullptr) {
				name++;
				if (name == '\\') {
					name++;
				}
				output << "\t" << '\"' << nameOfNode << '\"' << " -> " << '\"' << name << '\"';
				output << " [label=\"" << Alphabet::chr(i) << "\"]\n";
				name = draw_n(output, node->child(Alphabet::chr(i)), name);
			}
		}
		return name;
	}

	void swap(Trie& other) {
		using std::swap;
		swap(root_, other.root_);
	}

	/**
	 * Control validity of key, which is inserted to trie. If key is not valid, node.child throws
	 * exception. It guarantees consistance of trie.
	 * @param key Inserted key
	 */
	void validKey(const std::string& key) {
		for (char ch : key) {
			// it can throw exception
			root_.child(ch);
		}
	}

	void copyConstructor(Node* node, const Node* other) {
		for (int i = 0; i < Alphabet::size; i++) {
			if (other->value() != nullptr) {
				node->value_ = std::make_unique<Value>(*other->value_);
			}
			if (other->child(Alphabet::chr(i)) != nullptr) {
				node->succs_[i] = std::make_unique<Node>(node);
				copyConstructor(node->succs_[i].get(), other->child(Alphabet::chr(i)));
			}
		}
	}

public:
	Trie() = default;

	Trie(const Trie& other) {
		copyConstructor(&root_, &other.root());
	}

	Trie& operator=(Trie other) {
		swap(other);
		return *this;
	}
	const Node& root() const {
		return root_;
	}

	bool empty() const {
		return root_.succ_count_ == 0;
	}

	const Value* search(const std::string& key) const {
		const Node* node = find<const Node*>(*this, &root_, key);
		if (node == nullptr) {
			return nullptr;
		}
		return node->value();
	}

	Value* search(const std::string& key) {
		auto node = find<Node*>(*this, &root_, key);
		if (node == nullptr) {
			return nullptr;
		}
		return node->value_.get();
	}

	const Value& at(const std::string& key) const {
		const Node* node = find<const Node*>(*this, &root_, key);
		if (node != nullptr && node->value() != nullptr) {
			return *node->value();
		}
		throw std::out_of_range("Value for " + key + " not exists");
	}

	Value& at(const std::string& key) {
		auto node = find<Node*>(*this, &root_, key);
		if (node != nullptr && node->value() != nullptr) {
			return *node->value_;
		}
		throw std::out_of_range("Value for " + key + " not exists");
	}

	Value& operator[](const std::string& key) {
		bool alreadyExist = false;
		// 2*n == O(n)
		validKey(key);
		return *insert_n(&root_, key, 0, Value(), alreadyExist);
	}

	void remove(const std::string& key) {
		auto node = find<Node*>(*this, &root_, key);

		if (node == nullptr) {
			return;
		}

		node->value_.reset(nullptr);

		int index = key.size() - 1;
		bool deleted = node->succ_count_ == 0;
		node = node->parent_;

		while (index >= 0) {
			if (node == nullptr || !deleted) {
				return;
			}

			node->succs_[Alphabet::ord(key.at(index))].reset(nullptr);
			node->succ_count_--;
			deleted = node->succ_count_ == 0 && node->value() == nullptr;

			node = node->parent_;
			index--;
		}
	}

	bool insert(const std::string& key, const Value& value) {
		bool returnValue = false;
		// 2*n == O(n)
		validKey(key);
		insert_n(&root_, key, 0, value, returnValue);
		return returnValue;
	}

	void clear() {
		for (int i = 0; i < Alphabet::size; i++) {
			root_.succs_[i].reset(nullptr);
			root_.succ_count_ = 0;
		}
	}

	ItemList items() const {
		ItemList returnList;
		items_n(returnList, &root_, "");
		return returnList;
	}

	void draw(std::ostream& output) const {
		output << "digraph{\n";
		draw_n(output, &root_, 'A');
		output << "}\n";
	}
};

#endif
