#pragma once

class HashTable
{
public:


	class String
	{
	public:
		int key() const;
		String* next();

		void setKey(const int key);
		void setNext(const String* nextString);

	private:
		int m_key;
		String* m_nextString = nullptr;
	};



private:



};

