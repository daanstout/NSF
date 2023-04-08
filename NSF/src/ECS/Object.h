#pragma once

namespace NSF {
	class Object {
	private:
		static int currentId;
		static inline int GetNextId() { return ++currentId; }

	protected:
		int id;

	public:
		explicit Object() : id(Object::GetNextId()) {}

		inline int GetID() const { return id; }

		inline bool operator==(const Object& other) { return id == other.id; }
		inline bool operator!=(const Object& other) { return !(*this == other); }
		inline bool operator==(const Object* other) { return id == other->id; }
		inline bool operator!=(const Object* other) { return !(this == other); }
	};
}
