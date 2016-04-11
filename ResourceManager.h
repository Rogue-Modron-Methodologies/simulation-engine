
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

template <class T>
class ResourceManager
{
private:
	std::map<std::string, T> resources;

public:
	ResourceManager();
	~ResourceManager();
	const T& getResource(const std::string &fileName);
	void unloadResource(const T &resource);
	void unloadResource(const std::string &filename);

private:
	ResourceManager(const ResourceManager &temp) = delete;
	ResourceManager& operator =(const ResourceManager &temp) = delete;
};

template <class T>
ResourceManager<T>::ResourceManager() : resources() {}

template <class T>
ResourceManager<T>::~ResourceManager() { resources.clear(); }

template <class T>
const T& ResourceManager<T>::getResource(const std::string &filename)
{
	// If the resource already exists
	for (typename std::map<std::string, T>::const_iterator it = resources.begin(); it != resources.end(); it++)
	{
		if (filename == it->first)
			return it->second;
	}

	// Create and save it.
	T resource;
	if (resource.loadFromFile(filename))
	{
		resources[filename] = resource;
		return resources[filename];
	}

	// If not found, fill texture map with empty image
	std::cout << "ERROR: " << filename << " was not found.It will be filled with an empty texture.\n";
	resources[filename] = resource;
	return resources[filename];
}


template <class T>
void ResourceManager<T>::unloadResource(const T &resource)
{
	for (typename std::map<std::string, T>::const_iterator it = resources.begin(); it != resources.end(); it++)
	{
		if (&resource == &it->second)
		{
			resources.erase(it);
			return;
		}
	}
}

template <class T>
void ResourceManager<T>::unloadResource(const std::string &filename)
{
	typename std::map<std::string, T>::const_iterator it = resources.find(filename);
	if (it != resources.end())
		resources.erase(it);
}

#endif // RESOURCEMANAGER_H
