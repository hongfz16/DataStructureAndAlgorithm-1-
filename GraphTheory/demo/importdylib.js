var ffi = require('ffi'); 
var ref = require('ref');
var Struct = require('ref-struct');
var ArrayType = require('ref-array');

var intptr = ref.refType('int');
var intArray=ArrayType('int');

var edgeinfo = Struct({
	'u':'int',
	'v':'int',
	'w':'int'
});

var edgenode = Struct({
	'pdata':ref.refType(edgeinfo),
	'next':ref.refType('int')
});

var vertexinfo = Struct({});

var graphinfo = Struct({
	'n':'int',
	'm':'int',
	'elast':ref.refType(ref.refType(edgenode)),
	'v':ref.refType(vertexinfo)
});

var graphlib = ffi.Library('./native/main', 
	{
		'createGraph_n':[ref.refType(graphinfo),['int']],
		'destroyGraph':[ref.types.void,[ref.refType(graphinfo)]],
		'createEdgeInfo':[ref.refType(edgeinfo),['int','int','int']],
		'destroyEdgeInfo':[ref.types.void,[ref.refType(edgeinfo)]],
		'createGraph_s':[ref.refType(graphinfo),[ref.types.CString]],
		'dijkstraStep':[ref.types.void,[ref.refType(graphinfo),'int','int',intArray,ref.refType(edgeinfo)]],
		'dijkstra':[ref.types.void,[ref.refType(graphinfo),'int',intptr,ref.refType(edgeinfo)]]
	}); 


var svg = d3.select("svg"),
    width = +svg.attr("width"),
    height = +svg.attr("height");

var color = d3.scaleOrdinal(d3.schemeCategory20);

var simulation = d3.forceSimulation()
    .force("link", d3.forceLink().id(function(d) { return d.id; }))
    .force("charge", d3.forceManyBody())
    .force("center", d3.forceCenter(width / 2, height / 2));

d3.json("data.json", function(error, graph) {
  if (error) throw error;

  var link = svg.append("g")
      .attr("class", "links")
    .selectAll("line")
    .data(graph.links)
    .enter().append("line")
      .attr("id",function(d){return "id"+d.source+"_"+d.target;})
      .attr("stroke-width", function(d) { return Math.sqrt(d.value); });

  var node = svg.append("g")
      .attr("class", "nodes")
    .selectAll("circle")
    .data(graph.nodes)
    .enter().append("circle")
      .attr("r", 5)
      .attr("fill", function(d) { return color(d.group); })
      .call(d3.drag()
          .on("start", dragstarted)
          .on("drag", dragged)
          .on("end", dragended));

  node.append("title")
      .text(function(d) { return d.id; });

  simulation
      .nodes(graph.nodes)
      .on("tick", ticked);

  simulation.force("link")
      .links(graph.links);

  function ticked() {
    link
        .attr("x1", function(d) { return d.source.x; })
        .attr("y1", function(d) { return d.source.y; })
        .attr("x2", function(d) { return d.target.x; })
        .attr("y2", function(d) { return d.target.y; });

    node
        .attr("cx", function(d) { return d.x; })
        .attr("cy", function(d) { return d.y; });
  }
});

function dragstarted(d) {
  if (!d3.event.active) simulation.alphaTarget(0.3).restart();
  d.fx = d.x;
  d.fy = d.y;

  //changeLinkColor(d.id,"1");
  //console.log(d.id);

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


function changeLinkColor(source,target) {
  console.log(source,target);
  var targetlink=svg.select(".links").select("#id"+source.toString()+"_"+target.toString());
  var targetlink2=svg.select(".links").select("#id"+target.toString()+"_"+source.toString());
  targetlink.attr("stroke","#000");
  targetlink2.attr("stroke","#000");
  console.log("here");
}

function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}

async function bclk() {
	svg.select(".links").selectAll("line").attr("stroke","#fff");
	var filename=ref.allocCString('graphdata');
	var graph_ptr=graphlib.createGraph_s(filename);
	var edgeinfo_ptr=graphlib.createEdgeInfo(0,0,0);
	var dist_ptr=new intArray(17);
	for(var i=0;i<17;++i)
	{
		graphlib.dijkstraStep(graph_ptr,i,1,dist_ptr,edgeinfo_ptr);
		changeLinkColor(edgeinfo_ptr.deref().u,edgeinfo_ptr.deref().v);
		await sleep(200);
	}
	for(var i=0;i<17;++i)
	{
		console.log(dist_ptr[i]);
		console.log("-----");
	}
	graphlib.destroyGraph(graph_ptr);
	graphlib.destroyEdgeInfo(edgeinfo_ptr);
}