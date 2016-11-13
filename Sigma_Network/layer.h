/*
    This is a class definition for Sigma Net, which is a simple
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
//   File:          layer.h
//   Author:        Michael Koonts
//   Date:          April 7, 2016
//   Description:   Class definition of layer
//============================================================================
#pragma once
#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include <memory>
#include "sigmoid.h"

using namespace std;

class layer : public enable_shared_from_this<layer>
{
private:
    vector<sigmoid> m_layer;
    shared_ptr<layer> m_next;
    shared_ptr<layer> m_last;
    vector<shared_ptr<double>> m_input;
    vector<shared_ptr<double>> m_output;

public:

    //========================================================================
    // REQUIRES: Sigmoid class
    // MODIFIES: this
    // EFFECTS: Creates a sigle layer object with the same number of sigmoids
    //          as there are pointers in the output paramiter setting each 
    //          output for an individual simoid. Sets the input paramiter as 
    //          their input.  The last paramiter is treated as a pointer to 
    //          the layer that uses the input paramiter as its output.
    //========================================================================
    layer(
        vector<shared_ptr<double>> input,
        vector<shared_ptr<double>> output);
    //========================================================================
    // REQUIRES: Sigmoid class
    // MODIFIES: this
    // EFFECTS: Creates multiple layer objects with the number of sigmoids 
    //          indicated by the size paramiter, and sets the input paramiter 
    //          as their input.  The last paramiter is treated as a pointer to
    //          the layer that uses the input paramiter as its output.  This 
    //          constructor recursivly calls itself the number of times 
    //          indicated by the hidden paramiter and uses the above 
    //          constauctor as its base case
    //========================================================================
    layer(int size, vector<shared_ptr<double>> input);
    //========================================================================
    // REQUIRES: Constructor be finished
    // MODIFIES: this
    // EFFECTS: Set the pointer to the previous layer in the network if this 
    //          is the the output layer
    //========================================================================
    void init(shared_ptr<layer> previous);
    //========================================================================
    // REQUIRES: Constructor be finished
    // MODIFIES: this
    // EFFECTS: Set the pointer to the previous layer in the network and 
    //          create the next layer in the network
    //========================================================================
    void init(
        shared_ptr<layer> previous,
        unsigned int size,
        unsigned int hidden,
        vector<shared_ptr<double>> output);
    //========================================================================
    // REQUIRES: Nothing
    // MODIFIES: this
    // EFFECTS: Destroys this
    //========================================================================
    virtual ~layer();
    //========================================================================
    // REQUIRES: Nothing
    // MODIFIES: The values stored in the output vector
    // EFFECTS: Calculates the output for the values currently in the input 
    //          vector.
    //========================================================================
    void push();
    //========================================================================
    // REQUIRES: A vector to have been pushed
    // MODIFIES: this
    // EFFECTS: Part of the backward propagation algorithm (Called by the next 
    //          layer in the network)
    //========================================================================
    void train();
    //========================================================================
    // REQUIRES: A vector to have been pushed
    // MODIFIES: this (if this is the output layer)
    // EFFECTS: Trains each sigmoid in this layer OR passes the given vector 
    //          forward
    //========================================================================
    void train(vector<double> expected);
    //========================================================================
    // REQUIRES: One of the calculate<>Error methods to have beed called
    // MODIFIES: Nothing
    // EFFECTS: Returns the sum of the products of indexed weight and the 
    //          error for each sigmoid in the layer.
    //========================================================================
    double getError(unsigned int input);
    //========================================================================
    // REQUIRES: Nothing
    // MODIFIES: Nothing
    // EFFECTS: Add the member variable m_weights from each sigmoid in this to 
    //          given vector
    //========================================================================
    void getWeights(shared_ptr<vector<vector<double>>> weights);
    //========================================================================
    // REQUIRES: Nothing
    // MODIFIES: Nothing
    // EFFECTS: Pass each of the member sigmoids one of the given weight 
    //          vectors and pass the remainder to the next layer 
    //========================================================================
    void setWeights(vector<vector<double>>::iterator weights);
};

#endif