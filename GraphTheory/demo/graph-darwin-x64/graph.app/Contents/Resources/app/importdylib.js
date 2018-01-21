var ffi = require('ffi');
var ref = require('ref');
var Struct = require('ref-struct');
var ArrayType = require('ref-array');

var intptr = ref.refType('int');
var intArray = ArrayType('int');

var edgeinfo = Struct({
    'u': 'int',
    'v': 'int',
    'w': 'int'
});

var edgeinfoArray = ArrayType(edgeinfo);

var edgenode = Struct({
    'pdata': ref.refType(edgeinfo),
    'next': ref.refType('int')
});

var vertexinfo = Struct({});

var graphinfo = Struct({
    'n': 'int',
    'm': 'int',
    'elast': ref.refType(ref.refType(edgenode)),
    'v': ref.refType(vertexinfo)
});

var graphinfoptr = ref.refType(graphinfo);
var edgeinfoptr = ref.refType(edgeinfo);

var graphlib = ffi.Library('./native/main', {
    'createGraph_n': [ref.refType(graphinfo), ['int']],
    'destroyGraph': [ref.types.void, [ref.refType(graphinfo)]],
    'createEdgeInfo': [ref.refType(edgeinfo), ['int', 'int', 'int']],
    'destroyEdgeInfo': [ref.types.void, [ref.refType(edgeinfo)]],
    'createGraph_s': [ref.refType(graphinfo), [ref.types.CString]],
    'dijkstraStep': ['int', [ref.refType(graphinfo), 'int', 'int', intArray, ref.refType(edgeinfo),edgeinfoArray]],
    'dijkstra': ['int', [ref.refType(graphinfo), 'int', intptr, ref.refType(edgeinfo)]],
    'prim': ['int', [graphinfoptr, 'int', graphinfoptr]],
    'primStep': ['int', [graphinfoptr, 'int', 'int', edgeinfoptr]],
    'kruskal': ['int', [graphinfoptr, graphinfoptr]],
    'kruskalStep': [ref.types.bool, [graphinfoptr, 'int', edgeinfoptr]],
    'betweennessCentrality': [ref.types.void, [graphinfoptr, intArray]],
    'closenesscentrality': [ref.types.void, [graphinfoptr,intArray]]
});


var svg = d3.select("svg"),
    width = +svg.attr("width"),
    height = +svg.attr("height");

// var width = 1350,
//     height = 800;

// var canvas = d3.select("canvas")
//     .attr("width", width)
//     .attr("height", height);

var PATH = "../dataset/";
var randomjsonfilename = PATH + "jsonrandom.json";
var randomtxtfilename = PATH + "random.txt";
var filmjsonfilename = PATH + "filmgraph.json";
var filmtxtfilename = PATH + "filmgraph.txt";

var color = d3.scaleOrdinal(d3.schemeCategory20);

var simulation = d3.forceSimulation()
    .force("forceX", d3.forceX().strength(.3).x(width * .5))
    .force("forceY", d3.forceY().strength(.3).y(height * .5))
    .force("link", d3.forceLink().id(function(d) { return d.id; }))
    .force("charge", d3.forceManyBody())
    .force("center", d3.forceCenter(width / 2, height / 2));

var graphsize = 0;

var linkdata;
var nodedata;
var link;
var node;
var r = 1.5;


d3.json(filmjsonfilename, function(error, graph) {
    if (error) throw error;

    //glob_graph = graph;

    //var context = canvas.node().getContext("2d");

    linkdata = [];
    console.log(linkdata);
    nodedata = graph.nodes;

    link = svg.selectAll("line")
        .data(linkdata)
        .enter().append("line")
        .attr("class", "link")
        .attr("id", function(d) { return "id" + d.source + "_" + d.target; })
        .attr("stroke-opacity", function(d) { return 0; })
        .attr("stroke-width", function(d) { return 0.5; }); //Math.sqrt(d.value); });

    node = svg.selectAll("circle")
        .data(nodedata)
        .enter().append("circle")
        .attr("class", "node")
        .attr("id", function(d) { return "id" + d.id; })
        .attr("r", 2 * r)
        .attr("fill", function(d) { return color(d.group); })
        .call(d3.drag()
            .on("start", dragstarted)
            .on("drag", dragged)
            .on("end", dragended));

    console.log(node);

    graphsize = graph.nodes.length;

    node.on("click", function(d) {
        console.log("on click" + d.id);
        setTwoNodes(d.id);
    })

    node.append("title")
        .text(function(d) { return d.id; });

    simulation
        .nodes(graph.nodes)
        .on("tick", ticked);

    simulation.force("link")
        .links(linkdata);

    // function ticked() {
    //     context.clearRect(0, 0, width, height);

    //     // draw links
    //     context.strokeStyle = "rgba(255,255,255,0)";
    //     context.beginPath();
    //     graph.links.forEach(function(d) {
    //         if (d.opacity == 1)
    //             context.strokeStyle = "rgba(0,0,0,1)";
    //         context.moveTo(d.source.x, d.source.y);
    //         context.lineTo(d.target.x, d.target.y);
    //         context.strokeStyle = "rgba(255,255,255,0)";
    //     });
    //     context.stroke();

    //     // draw nodes
    //     context.fillStyle = "steelblue";
    //     context.beginPath();
    //     graph.nodes.forEach(function(d) {
    //         context.moveTo(d.x = Math.max(r, Math.min(width - r, d.x)), d.y = Math.max(r, Math.min(height - r, d.y)));
    //         context.arc(d.x, d.y, 3, 0, 2 * Math.PI);
    //     });
    //     context.fill();

    // }


});

function ticked() {
    link
        .attr("x1", function(d) { return d.source.x; })
        .attr("y1", function(d) { return d.source.y; })
        .attr("x2", function(d) { return d.target.x; })
        .attr("y2", function(d) { return d.target.y; });

    node
        .attr("cx", function(d) { return d.x = Math.max(r, Math.min(width - r, d.x)); })
        .attr("cy", function(d) { return d.y = Math.max(r, Math.min(height - r, d.y)); });
    //.attr("cx", function(d) { return d.x; })
    //.attr("cy", function(d) { return d.y; });
}

function dragstarted(d) {
    if (!d3.event.active) simulation.alphaTarget(0.3).restart();
    d.fx = d.x;
    d.fy = d.y;

}

function dragged(d) {
    d.fx = d3.event.x;
    d.fy = d3.event.y;
}

function dragended(d) {
    if (!d3.event.active) simulation.alphaTarget(0);
    d.fx = null;
    d.fy = null;
}


function changeLinkColor(_source, _target) {
    console.log(_source, _target);

    simulation.stop();
    linkdata.push({ source: nodedata[_source], target: nodedata[_target], value: 30 });


    //console.log(linkdata);

    // svg.selectAll(".link").remove();
    // svg.selectAll(".node").remove();

    // node = svg.selectAll("circle")
    //     .data(nodedata)
    //     .enter().append("circle")
    //     .attr("class", "node")
    //     .attr("id", function(d) { return "id" + d.id; })
    //     .attr("r", 2 * r)
    //     .attr("fill", function(d) { return color(d.group); })
    //     .call(d3.drag()
    //         .on("start", dragstarted)
    //         .on("drag", dragged)
    //         .on("end", dragended));

    // link = svg.selectAll("line")
    //     .data(linkdata)
    //     .enter().append("line")
    //     .attr("class", "link")
    //     .attr("id", function(d) { return "id" + d.source.id + "_" + d.target.id; })
    //     .attr("stroke-opacity", function(d) { return 1; })
    //     .attr("stroke-width", function(d) { return 0.5; });

    node.data(nodedata)
      .enter()
      .append("circle")
        .attr("class", "node")
        .attr("id", function(d) { return "id" + d.id; })
        .attr("r", 2 * r)
        .attr("fill", function(d) { return color(d.group); })
        .call(d3.drag()
            .on("start", dragstarted)
            .on("drag", dragged)
            .on("end", dragended));

    link.data(linkdata)
        .enter().append("line")
        .attr("class", "link")
        .attr("id", function(d) { return "id" + d.source.id + "_" + d.target.id; })
        .attr("stroke-opacity", function(d) { return 0; })
        .attr("stroke-width", function(d) { return 0.5; });

    node = svg.selectAll(".node");
    link = svg.selectAll(".link");

    simulation
        .nodes(nodedata)
        .on("tick", ticked);

    simulation.force("link")
        .links(linkdata);

    //ticked();
    simulation.restart();
    //console.log(node, link, nodedata, linkdata);
    //simulation.restart();

    //console.log(node);

    //simulation.restart();
    // glob_graph.links.forEach(function(d) {
    //     if (d.source == source && d.target == target)
    //         d.opacity = 1;
    // });
    var targetlink = svg.select("#id" + _source.toString() + "_" + _target.toString());
    //var targetlink2 = svg.select(".links").select("#id" + _target.toString() + "_" + _source.toString());
    targetlink.attr("stroke", "#000");
    targetlink.attr("stroke-opacity", 0.8);
    //targetlink2.attr("stroke", "#000");
    //targetlink2.attr("stroke-opacity", 0.8);

}

function changeNodeColor(id, centerality) {
    var targetnode = svg.select("#id" + id.toString());
    targetnode.attr("fill", color(centerality));
}

function setTwoNodes(id) {
    var numberform = document.getElementById("inputnumber");
    var strfirstnumber = numberform.elements[0].value;
    var strsecondnumber = numberform.elements[1].value;
    if (strfirstnumber === "")
        numberform.elements[0].value = id;
    else if (strsecondnumber === "")
        numberform.elements[1].value = id;
    else {
        numberform.elements[0].value = strsecondnumber;
        numberform.elements[1].value = id;
    }
}

function getTwoNodes() {
    var numberform = document.getElementById("inputnumber");
    var strfirstnumber = numberform.elements[0].value;
    var strsecondnumber = numberform.elements[1].value;
    if (strfirstnumber === "" || strsecondnumber === "")
        return [-1, -1];
    var firstnum = parseInt(strfirstnumber);
    var secondnum = parseInt(strsecondnumber);
    return [firstnum, secondnum];
}

function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

async function dijkstraButtonClk() {
    var nnum = graphsize;
    var sourceandtarget = getTwoNodes();
    if (sourceandtarget[0] == -1)
        return;
    svg.selectAll(".link").remove();
    var filename = ref.allocCString(filmtxtfilename);
    var graph_ptr = graphlib.createGraph_s(filename);
    var edgeinfo_ptr = graphlib.createEdgeInfo(0, 0, 0);
    var dist_ptr = new intArray(nnum);
    for (var i = 0; i < nnum; ++i) {
        graphlib.dijkstraStep(graph_ptr, i, sourceandtarget[0], dist_ptr, edgeinfo_ptr);
        changeLinkColor(edgeinfo_ptr.deref().u, edgeinfo_ptr.deref().v);
        await sleep(10);
    }
    document.getElementById("dijkstraresult").innerHTML = "The length of the shortest way is " + dist_ptr[sourceandtarget[1]];
    graphlib.destroyGraph(graph_ptr);
    graphlib.destroyEdgeInfo(edgeinfo_ptr);
}

async function primButtonClk() {
    var nnum = graphsize;
    //svg.selectAll(".link").attr("stroke", "#fff");
    svg.selectAll(".link").remove();
    var filename = ref.allocCString(filmtxtfilename);
    var graph_ptr = graphlib.createGraph_s(filename);
    var edgeinfo_ptr = graphlib.createEdgeInfo(0, 0, 0);
    for (var i = 0; i < nnum; ++i) {
        graphlib.primStep(graph_ptr, i, 0, edgeinfo_ptr);
        changeLinkColor(edgeinfo_ptr.deref().u, edgeinfo_ptr.deref().v);
        //break;
        await sleep(10);
    }
    //console.log("out");
    graphlib.destroyGraph(graph_ptr);
    graphlib.destroyEdgeInfo(edgeinfo_ptr);
}

async function kruskalButtonClk() {
    var nnum = graphsize;
    //svg.selectAll(".link").attr("stroke", "#fff");
    svg.selectAll(".link").remove();
    var filename = ref.allocCString(randomtxtfilename);
    var graph_ptr = graphlib.createGraph_s(filename);
    var edgeinfo_ptr = graphlib.createEdgeInfo(0, 0, 0);
    for (var i = 0; i < nnum - 1; ++i) {
        graphlib.kruskalStep(graph_ptr, i, edgeinfo_ptr);
        changeLinkColor(edgeinfo_ptr.deref().u, edgeinfo_ptr.deref().v);
        await sleep(10);
    }
    graphlib.destroyGraph(graph_ptr);
    graphlib.destroyEdgeInfo(edgeinfo_ptr);
    simulation.restart();
}

async function betweennessCenteralityButtonClk() {
    var nnum = graphsize;
    var filename = ref.allocCString(randomtxtfilename);
    var graph_ptr = graphlib.createGraph_s(filename);
    var nodeCenteralityArray = new intArray(nnum);
    graphlib.betweennessCentrality(graph_ptr, nodeCenteralityArray);
    var max = 0;
    var min = 99999;
    for (var i = 0; i < nnum; ++i) {
        if (nodeCenteralityArray[i] > max)
            max = nodeCenteralityArray[i];
        if (nodeCenteralityArray[i] < min)
            min = nodeCenteralityArray[i];
    }
    color = d3.scaleLinear().domain([min, max])
        .interpolate(d3.interpolateHcl)
        .range([d3.rgb("#007AFF"), d3.rgb('#FFF500')]);

    for (var i = 0; i < nnum; ++i) {
        changeNodeColor(i, nodeCenteralityArray[i]); //Math.floor(nodeCenteralityArray[i]/max*20)+1);
    }
}

//TODO:prim和最短路等算法的循环次数（图不连通）、最短路画出路径、最小支撑树想办法弄漂亮点、项目结构设计、中心度结果预处理