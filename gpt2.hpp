#pragma once

#include<vector>
#include<random>
#include<memory>
#include<thread>
#include<assert.h>
#include<iostream>

using std::vector;
// using Matrix2Dim = std::unique_ptr<vector<vector<float>>>;
using Matrix2Dim = vector<vector<float>>*;

class Matrix2Dim
{
public:
    using Matrix2DimBase = vector<vector<float>>;
    using Matrix2DimPtr = Matrix2DimBase*;

    Matrix2Dim(int row_dim,int column_dim):row_dim_(row_dim),column_dim_(column_dim){}
    ~Matrix2Dim() 
    {
        
    }

    Matrix2Dim* operator+(Matrix2Dim* r) const 
    {   
        if(row_dim_ != r->row_dim_ || column_dim_ != r->column_dim_) {
            std::cerr << "shape not match" << std::endl;
            abort();
        }
        Matrix2Dim* result = new Matrix2Dim(row_dim_);
        // simple implement
        for(size_t i = 0;i < row_num_;++i) {

        }
    }

    int row_dim_;
    int column_dim_;
    Matrix2DimPtr data_;
};

class GPT2
{
private:
    int vocab_size_;
    int emb_dim_;
    int context_length_;

   Matrix2Dim tok_emb_;
   Matrix2Dim pos_emb_;
public:
    GPT2(int vocab_size,int emb_dim,int context_length)
    {
        tok_emb_= create_embedding(vocab_size,emb_dim);
        pos_emb_ = create_embedding(context_length,emb_dim);

    }

    // overload () to call forward()
    template<typename T>
    void operator()(T&& idxs)
    {
        forward(std::forward<T>(idxs));
    }

private:
    template<typename T>
    void forward(T&& idxs)
    {
        // // Crop current context if it exceeds the supported context size
        // if(idxs.size() > context_length_) {
        //     idxs = std::move(idxs.end() - ,)
        // }
        Matrix2Dim tok_emb = query(tok_emb_,idxs);
        vector<int> pos_idxs(idxs.size());
        for(int i = 0;i < pos_idx.size();++i) {
            pos_idxs[i] = i;
        }
        Matrix2Dim pos_emb = query(pos_emb_,pos_idxs);

        // for(size_t i = 0;i < idxs.size();++i) {
        //     for(size_t j = 0;j < 3;++j) {
        //         std::cout << (*ret)[i][j] << " ";
        //     }
        //     std::cout << std::endl;
        // }
    }

    // only support idx which dim is 1
    Matrix2Dim query(Matrix2Dim weights,const vector<int>& idxs) const 
    {
        Matrix2Dim query_ret = new vector<vector<float>>(idxs.size());
        size_t i = 0;
        for(const auto& idx : idxs) {
            if(idx < 0 || idx >= weights->size()) {
                std::cerr << "idx error:" << idx << " is out of bounds\n";
                abort();
            }
            for(size_t j = 0;j < (*weights)[idx].size();++j) {
                (*query_ret)[i].push_back((*weights)[idx][j]);
            }
            i++;
        }
        return query_ret;
    }

    // use gaussian distribution
    Matrix2Dim create_embedding(int row_dim,int column_dim,float mean = 0.0,float stddev = 1.0)
    {
        // todo: should handle memory exception
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<float> dist(mean,stddev);

        Matrix2Dim embedding = new vector<vector<float>>(row_dim);

        for(size_t i = 0;i < row_dim;++i) {
            (*embedding)[i].resize(column_dim);
            for(size_t j = 0;j < column_dim;++j) {
                (*embedding)[i][j] = dist(gen);
            }
        }

        // print 
        // for(size_t i = 0;i < embedding->size();++i) {
        //     for(size_t j = 0;j < (*embedding)[i].size();++j) {
        //         std::cout << (*embedding)[i][j] << " ";
        //     }
        //     std::cout << std::endl;
        // }

        return embedding;
    }
};

