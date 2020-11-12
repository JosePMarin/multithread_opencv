#pragma once
#include "common.hpp"

// Object adapter that wraps cv::Mat and creates and interface in order to
// create matrix easier and with custom data type defined
template <typename data_vector>
class matrix_adapter
{
    private:
        int m_row;
        int m_col;
        std::tuple<data_vector> m_content;
        std::vector<std::vector<data_vector>> m_matrix_content;
    public:
        // Requires definition of matrix number of columns
        matrix_adapter(int size) : m_row{size} {}

        // Creates a matrix from inserting vectors with predefined range
        void insert_vector(data_vector data)
        {
            std::vector<data_vector> matrix_vect;
            m_content = std::make_tuple(data);
            for (int i = 0; i < m_row - 1; i++)
            {
                matrix_vect.push_back(std::get<i>(m_content));
            }
            m_matrix_content.push_back(std::move(matrix_vect));
        }
        // Creates a matrix from the buffered vectors 
        cv::Mat create_matrix(int type=CV_8UC1)
        {   
            std::vector<data_vector> data;
            int m_col = m_matrix_content.size();
            for (auto vector_row : m_matrix_content)
            {
                for (auto element_row : vector_row)
                {
                    data.push_back(element_row);
                }
            }
            return cv::Mat(m_row, m_col, type, data);
        }

        ~matrix_adapter();
};


