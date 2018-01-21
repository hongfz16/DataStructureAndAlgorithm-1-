var ffi = require('ffi');
var ref = require('ref');
var Struct = require('ref-struct');
var ArrayType = require('ref-array');

var PATH = "../dataset/";
var randomjsonfilename = PATH + "jsonrandom.json";
var randomtxtfilename = PATH + "random.txt";
var filmjsonfilename = PATH + "filmgraph.json";
var filmtxtfilename = PATH + "filmgraph.txt";

function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

var working=false;
var stopflag=false;