#ifndef SPARSE_H
#define SPARSE_H

#include <unordered_map>
#include <stdexcept>

class position
{
    private:
        int x;
        int y;
    
    public:
        position() {}
        position(int x, int y)
        {
            if (x < 0 || y < 0)
            {
                throw std::invalid_argument("Position cannot be negative.");
            }
            
            this->x = x;
            this->y = y;
        }
        
        friend bool operator==(const position& left, const position& right)
        {
            return (left.x == right.x && left.y == right.y);
        }
        
        const int get_x() const
        {
            return x;
        }
        const int get_y() const
        {
            return y;
        }
};

template <class T>
class sparse
{
    private:
        int rows;
        int columns;
        std::unordered_map<position, T> matrix;
        T defaultValue = T();
    
    public:
        sparse() {}
        sparse(int rows, int columns)
        {
            this->rows = rows;
            this->columns = columns;
        }
        
        void add(const T& value, position p)
        {
            if (p.get_x() >= rows || p.get_y() >= columns)
            {
                throw std::invalid_argument("Out of range.");
            }
            
            if (value != defaultValue)
            {
                matrix[p] = value;
            }
        }
        
        const T& at(int x, int y)
        {
            if (x >= rows || y >= columns)
            {
                throw std::invalid_argument("Out of range.");
            }
            
            auto it = matrix.find(position(x, y));
            if (it == matrix.end())
            {
                return defaultValue;
            }
            return it->second;
        }
};

#endif