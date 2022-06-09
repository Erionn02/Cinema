#ifndef INTRODUCTIONPROJECT_REPOSITORY_H
#define INTRODUCTIONPROJECT_REPOSITORY_H
#include "typedefs.h"
#include <vector>
#include <algorithm>
#include "Exceptions/CinemaException.h"
#include <iostream>
template<class T> class Repository{
private:
    std::vector<std::shared_ptr<T>> repository;
public:
    const std::vector<std::shared_ptr<T>> &getRepository() const
    {
        return repository;
    }
    Repository(){

    }
    virtual ~Repository(){}
    void add(std::shared_ptr<T> object)
    {
        if(!object)throw CinemaException("Given object does not exist");
        bool flag=true;
        for(int i=0;i<repository.size();i++)
        {
            if(repository[i]==object)
            {
                flag=false;
                break;
            }
        }
        if(!flag)throw CinemaException("Given object already exists in repository");
        repository.push_back(object);
    }
    void remove(std::shared_ptr<T> object){
        if(!object) throw CinemaException("Given object does not exist");
        bool flag=true;
        for(int i=0;i<repository.size();i++)
        {
            if(repository[i]==object)
            {
                flag=false;
                break;
            }
        }
        if(flag)throw CinemaException("Repository does not contain given object");
        repository.erase(std::remove(repository.begin(),repository.end(),object),repository.end());
    }
    std::shared_ptr<T> getObject(int id)const
    {
        std::shared_ptr<T> obj;
        std::shared_ptr<T> obj2;
        for(int i=0;i<repository.size();i++)
        {
            if(repository[i]->getId()==id)
            {
                obj=repository[i];
                break;
            }
            obj2=repository[i];
        }
        if(!obj)throw CinemaException("Could not find object with given id"+ std::to_string(id));
        return obj;
    }
    std::shared_ptr<T> getObjectByIndex(int index)const
    {
        if(index<0||index>=repository.size())throw CinemaException("Given index is out of range");
        return repository[index];
    }
    std::string getObjectsInfo()const
    {
        std::string s="";
        for(int i=0;i<repository.size();i++)
        {
            s+=repository[i]->getInfo()+"\n";
        }
        return s;
    }
    int getSize()const
    {
        return repository.size();
    }
    template <typename Predicate>  std::vector<std::shared_ptr<T>> findBy(Predicate p)const{
        std::vector<std::shared_ptr<T>> tmp;
        for(int i =0;i<repository.size();i++)
        {
            std::shared_ptr<T> obj=repository[i];
            if(p(obj) && obj)tmp.push_back(obj);
        }
        return tmp;
    }
    std::vector<std::shared_ptr<T>> findAll()const
    {
        std::function<bool(std::shared_ptr<T>)> f=[](std::shared_ptr<T> obj)->bool
        {
            return true;
        };
        return findBy(f);//funkcja w zasadzie jest getterem, ale potrzebna do testow itp
    }
    std::string getObjectInfo(std::shared_ptr<T> object)const
    {
        if(!object)throw CinemaException("Given object does not exist");
        return object->getInfo();
    }
};



#endif //INTRODUCTIONPROJECT_REPOSITORY_H
