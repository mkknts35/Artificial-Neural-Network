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
//   File:          network.h
//   Author:        Michael Koonts
//   Date:          April 7, 2016
//   Description:   Class definition of network. This class is part of an 
//                  artificial neural network. It is intended to be used in 
//                  conjunction with two other classes: layer and sigmoid. The
//                  only of these two classes that this class interacts with 
//                  directly is the layer class, because the network consists
//                  of a series of layers.
//============================================================================
#pragma once
#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <memory>
#include <fstream>
#include <iostream>
#include <sstream>
#include "layer.h"

using namespace std;

class network
{
private:
    string m_name;

    // network specification
    unsigned int m_inputs, m_outputs, m_layers, m_layerSize;

    shared_ptr<layer> m_network;
    vector<shared_ptr<double>> m_input;
    vector<shared_ptr<double>> m_output;

public:

    //========================================================================
    // REQUIRES: layer class
    // MODIFIES: this
    // EFFECTS:  Initializes a new neural network
    //========================================================================
    network(
        string name,
        unsigned int inputs,
        unsigned int outputs,
        unsigned int layers,
        unsigned int layerSize);
    //========================================================================
    // REQUIRES: layer class
    // MODIFIES: this
    // EFFECTS:  Initializes a neural network that is to be restored from file
    //========================================================================
    network(string name);
    //========================================================================
    // REQUIRES: Nothing
    // MODIFIES: this
    // EFFECTS: Destroys this
    //========================================================================
    ~network();
    //========================================================================
    // REQUIRES: Two vectors of doubles the same size as the number of 
    //           inputs/outputs the network was intialized with.
    // MODIFIES: This
    // EFFECTS:  Changes the weights of all the inputs in the network
    //========================================================================
    void train(vector<double> input, vector<double> output);
    //========================================================================
    // REQUIRES: A vector of doubles the same size as the number of inputs as 
    //           the network was initialized with.
    // MODIFIES: Nothing
    // EFFECTS:  Pushes the given vector through the network and returns the 
    //           result.
    //========================================================================
    vector<double> push(vector<double> input);
    //========================================================================
    // The following methods work together to make the network persistant. 
    // They create and use a file named <m_name>.ann which contains the 
    // network specification and the weights used by all the sigmoids in the 
    // system.  The first line of this file should be the network 
    // specification seperated by white space.  Each of the following lines 
    // should contain the weights of a single sigmoid seperated by white 
    // space.
    //      eg. 4 3 1 3
    //          -0.931549 -1.26498 1.27358 2.71645
    //          1.14696 0.298329 0.206592 0.217725
    //          0.84882 0.721978 0.483424 0.663198
    //          10.8642 -0.658323 -1.36494
    //          -10.3253 3.86111 3.83712
    //          0.39034 1.96746 2.53561
    //          -8.06255 3.88009 0.216352
    //          6.32053 6.33108 -9.56196
    //          5.06881 -8.33005 -0.91167                
    //------------------------------------------------------------------------
    // REQUIRES: Nothing
    // MODIFIES: the file <m_name>.ann
    // EFFECTS: Writes the current specifications and weights of the network 
    //          to the file system
    //------------------------------------------------------------------------
    void writeNetwork();
    //------------------------------------------------------------------------
    // REQUIRES: Nothing
    // MODIFIES: this
    // EFFECTS: Attempt to locate a previously saved network in the from of a
    //          file by the name of <m_name>.ann.  If the file exists, use it
    //          to restore the network and return true, otherwise retrun false
    //========================================================================
    bool restoreNetwork();

private:

    //========================================================================
    // REQUIRES: Nothing
    // MODIFIES: Nothing
    // EFFECTS: Collects and returns all the weights currently being used in 
    //          the network
    //========================================================================
    shared_ptr<vector<vector<double>>> getWeights();
    //========================================================================
    // REQUIRES: The arguement vector's properties must match this' spec
    // MODIFIES: this
    // EFFECTS: Sets the weights in the network to the ones in the arguement
    //          vector (there must be a double for each sigmoid in the network)
    //========================================================================
    void setWeights(vector<vector<double>> weights);

};

#endif