var ffi = require('ffi');
var ref = require('ref');
var Struct = require('ref-struct');
var ArrayType = require('ref-array');

var PATHJSON = "../dataset/";
var PATHTXT = "./dataset";
var randomjsonfilename = PATHJSON + "jsonrandom.json";
var randomtxtfilename = PATHTXT + "random.txt";
var filmjsonfilename = PATHJSON + "filmgraph.json";
var filmtxtfilename = PATHTXT + "filmgraph.txt";

function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

var working=false;
var stopflag=false;