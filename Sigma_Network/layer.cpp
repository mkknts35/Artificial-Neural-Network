/*
    This is a class implementation for Sigma Net, which is a simple
    Artificial Neural Network

    Copyright(C) 2016  Michael Brett Koonts

    This program is free software : you can redistribute it and / or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//============================================================================
//   File:      layer.cpp
//   Author:    Michael Koonts
//   Date :     April 7, 2016
//============================================================================
#include "layer.h"
//============================================================================
// public
//============================================================================
layer::layer(
    vector <shared_ptr<double>> input,
    vector <shared_ptr<double>> output
    )
{
    m_last = nullptr;
    m_next = nullptr;
    for (unsigned int i = 0; i < output.size(); i++) {
        m_layer.push_back(sigmoid(input, output.at(i), false));
    }
}
//============================================================================
layer::layer(int size, vector <shared_ptr<double>> input)
{
    m_last = nullptr;
    m_next = nullptr;
    shared_ptr<double> out;
    for (int i = 0; i < size; i++) {
        out = make_shared<double>(0);
        m_layer.push_back(sigmoid(input, out));
        m_output.push_back(out);
    }
}
//========================================================================
void layer::init(shared_ptr<layer> previous)
{
    m_last = previous;
}
//========================================================================
void layer::init(
    shared_ptr<layer> previous, 
    unsigned int size, 
    unsigned int hidden, 
    vector<shared_ptr<double>> output
    )
{
    m_last = previous;
    if (hidden > 0) {
        m_next = make_shared<layer>(size, m_output);
        m_next->init(shared_from_this(), size, hidden - 1, output);
    } else {
        m_next = make_shared<layer>(m_output, output);
        m_next->init(shared_from_this());
    }
}
//============================================================================
layer::~layer()
{
}
//============================================================================
void layer::push()
{
    for (unsigned int i = 0; i < m_layer.size(); i++) {
        m_layer.at(i).push();
    }
    if (m_next != nullptr) {
        m_next->push();
    }
}
//============================================================================
void layer::train()
{
    for (unsigned int i = 0; i < m_layer.size(); i++) {
        m_layer.at(i).train(m_next->getError(i));
    }
    if (m_last != nullptr) {
        m_last->train();
    }
}
//============================================================================
void layer::train(vector<double> expected)
{
    if (m_next != nullptr) {
        m_next->train(expected);
    } else {
        for (unsigned int i = 0; i < m_layer.size(); i++) {
            m_layer.at(i).train(expected.at(i));
        }
        if (m_last != nullptr) {
            m_last->train();
        }
    }
}
//============================================================================
double layer::getError(unsigned int input)
{
    double error = 0;
    for (unsigned int i = 0; i < m_layer.size(); i++) {
        error += m_layer.at(i).getWeightedError(input);
    }
    return error;
}
//============================================================================
void layer::getWeights(shared_ptr<vector<vector<double>>> weights)
{
    //vector<vector<double>> weights;
    vector<sigmoid>::iterator current = m_layer.begin();
    while (current != m_layer.end()) {
        weights->push_back(current->getWeights());
        current++;
    }
    if (m_next != nullptr) {
        m_next->getWeights(weights);
    }
}
//============================================================================
void layer::setWeights(vector<vector<double>>::iterator weights)
{
    vector<sigmoid>::iterator sig = m_layer.begin();
    while (sig != m_layer.end()) {
        sig->setWeights(*weights);
        sig++;
        weights++;
    }
    if (m_next != nullptr) {
        m_next->setWeights(weights);
    }
}