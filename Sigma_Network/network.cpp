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
//   File:      network.cpp
//   Author:    Michael Koonts
//   Date :     April 7, 2016
//============================================================================
#include "network.h"
//============================================================================
// public
//============================================================================
network::network(
    string name,
    unsigned int inputs,
    unsigned int outputs,
    unsigned int layers,
    unsigned int layerSize)
{
    for (unsigned int i = 0; i < inputs; i++) {
        m_input.push_back(make_shared<double>(0));
    }
    for (unsigned int i = 0; i < outputs; i++) {
        m_output.push_back(make_shared<double>(0));
    }
    m_name = name;
    m_inputs = inputs;
    m_outputs = outputs;
    m_layers = layers;
    m_layerSize = layerSize;
    m_network = make_shared<layer>(layerSize, m_input);
    m_network->init(nullptr, layerSize, layers, m_output);
}
//============================================================================
network::network(string name)
{
    m_name = name;
}
//============================================================================
network::~network()
{
}
//============================================================================
void network::train(vector<double> input, vector<double> output)
{
    if (input.size() != m_input.size()) {
        return;
    } else {
        for (unsigned int i = 0; i < m_input.size(); i++) {
            *m_input.at(i) = input.at(i);
        }
        m_network->push();
        m_network->train(output);
    }
}
//============================================================================
vector<double> network::push(vector<double> input)
{
    vector<double> output;
    if (input.size() != m_input.size()) {
        for (unsigned int i = 0; i < m_output.size(); i++) {
            output.push_back(-1);
        }
    } else {
        for (unsigned int i = 0; i < m_input.size(); i++) {
            *m_input.at(i) = input.at(i);
        }
        m_network->push();
        for (unsigned int i = 0; i < m_output.size(); i++) {
            output.push_back(*m_output.at(i));
        }
    }
    return output;
}
//============================================================================
void network::writeNetwork()
{
    ofstream fout;
    string file = m_name + ".ann";
    fout.open(file);
    if (!fout) {
        cerr << "Error: cannot create backup file." << endl;
    } else {
        shared_ptr<vector<vector<double>>> weights = this->getWeights();
        fout << m_inputs << " " << m_outputs << " " << m_layers << " "
            << m_layerSize << endl;
        for (vector<vector<double>>::iterator it = weights->begin();
            it != weights->end(); it++) {
            for (vector<double>::iterator i = it->begin(); i != it->end();
                i++) {
                fout << *i << " ";
            }
            fout << endl;
        }
        fout.close();
    }
}
//============================================================================
bool network::restoreNetwork()
{
    ifstream fin;
    string file = m_name + ".ann";

    if (ifstream(file)) {
        fin.open(file);
        if (!fin) {
            cerr << "Error: cannot read backup file." << endl;
            return false;
        } else {
            stringstream buffer;
            string line;

            // The first line is the network specs
            getline(fin, line);
            buffer << line;
            buffer >> m_inputs;
            buffer >> m_outputs;
            buffer >> m_layers;
            buffer >> m_layerSize;

            //initialize the network
            for (unsigned int i = 0; i < m_inputs; i++) {
                m_input.push_back(make_shared<double>(0));
            }
            for (unsigned int i = 0; i < m_outputs; i++) {
                m_output.push_back(make_shared<double>(0));
            }
            m_network = make_shared<layer>(m_layerSize, m_input);
            m_network->init(nullptr, m_layerSize, m_layers, m_output);

            //extract the weights from the file
            vector<vector<double>> weights;
            while (!fin.eof()) {
                getline(fin, line);
                line = line.substr(0, line.length() - 1);
                buffer.clear();
                buffer << line;
                double weight;
                vector<double> layerWeights;
                while (!buffer.eof()) {
                    buffer >> weight;
                    layerWeights.push_back(weight);
                }
                weights.push_back(layerWeights);
            }
            fin.close();
            //restore the saved network
            setWeights(weights);
            return true;
        }
    } else {
        return false;
    }
}
//============================================================================
// private
//============================================================================
shared_ptr<vector<vector<double>>> network::getWeights()
{
    shared_ptr<vector<vector<double>>> weights;
    weights = make_shared<vector<vector<double>>>();
    m_network->getWeights(weights);
    return weights;
}
//============================================================================
void network::setWeights(vector<vector<double>> weights)
{
    m_network->setWeights(weights.begin());
}
//============================================================================
