var svg = d3.select("svg"),
    width = +svg.attr("width"),
    height = +svg.attr("height");

var color = d3.scaleOrdinal(d3.schemeCategory20);

var simulation = d3.forceSimulation()
    .force("forceX", d3.forceX().strength(.35).x(width * .5))
    .force("forceY", d3.forceY().strength(.35).y(height * .5))
    .force("link", d3.forceLink().id(function(d) { return d.id; }))
    .force("charge", d3.forceManyBody())
    .force("center", d3.forceCenter(width / 2, height / 2));

var graphsize = 0;
var vsize=0;
var linkdata = [];
var nodedata = [];
var link;
var node;
var r = 1.5;
var strokewidth = 0.5;

d3.json(filmjsonfilename, function(error, graph) {
    if (error) throw error;
    nodedata = graph.nodes;
    graphsize = graph.nodes.length;
    vsize=graph.links.length;

    link = svg.selectAll("line")
        .data(linkdata)
        .enter().append("line")
        .attr("class", "link")
        .attr("id", function(d) { return "id" + d.source + "_" + d.target; })
        .attr("stroke-opacity", function(d) { return 1; })
        .attr("stroke", "#000")
        .attr("stroke-width", function(d) { return strokewidth; }); //Math.sqrt(d.value); });

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
    simulation
        .nodes(nodedata)
        .on("tick", ticked);

    simulation.force("link")
        .links(linkdata);

    node.on("click", function(d) {
        console.log("on click" + d.id);
        dijkstraApp.setTwoNodes(d.id);
        var infostr="Node Info:<br>id: " + d.id + "<br>name: "+nodedata[parseInt(d.id)].name;
        if(betweenCenteralityApp.nodeCenteralityArray!=0)
            infostr+=("<br>BC: "+betweenCenteralityApp.nodeCenteralityArray[parseInt(d.id)]);
        if(closenessCenteralityApp.nodeCenteralityArray!=0)
            infostr+=("<br>CC: "+closenessCenteralityApp.nodeCenteralityArray[parseInt(d.id)]);
        showinfo(infostr);
    });
});

function showinfo(str) {
    var infoob = document.getElementById("info");
    infoob.innerHTML = str;
}

function redrawGraph() {

    simulation.stop();

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
        .attr("stroke-opacity", function(d) { return 1; })
        .attr("stroke", "#000")
        .attr("stroke-width", function(d) { return strokewidth; });

    node = svg.selectAll(".node");
    link = svg.selectAll(".link");

    simulation
        .nodes(nodedata)
        .on("tick", ticked);

    simulation.force("link")
        .links(linkdata);

    simulation.restart();
}

function removeAndRedraw() {
    simulation.stop();

    svg.selectAll("circle").remove();
    svg.selectAll("line").remove();

    link = svg.selectAll("line")
        .data(linkdata)
        .enter().append("line")
        .attr("class", "link")
        .attr("id", function(d) { return "id" + d.source + "_" + d.target; })
        .attr("stroke-opacity", function(d) { return 1; })
        .attr("stroke", "#000")
        .attr("stroke-width", function(d) { return strokewidth; }); //Math.sqrt(d.value); });

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
    
    node.on("click", function(d) {
        console.log("on click" + d.id);
        dijkstraApp.setTwoNodes(d.id);
        var infostr="Node Info:<br>id: " + d.id + "<br>name: "+nodedata[parseInt(d.id)].name;
        if(betweenCenteralityApp.nodeCenteralityArray!=0)
            infostr+=("<br>BC: "+betweenCenteralityApp.nodeCenteralityArray[parseInt(d.id)]);
        if(closenessCenteralityApp.nodeCenteralityArray!=0)
            infostr+=("<br>CC: "+closenessCenteralityApp.nodeCenteralityArray[parseInt(d.id)]);
        showinfo(infostr);
        console.log(parseInt(d.id));
    })

    simulation = d3.forceSimulation()
        .force("forceX", d3.forceX().strength(.35).x(width * .5))
        .force("forceY", d3.forceY().strength(.35).y(height * .5))
        .force("link", d3.forceLink().id(function(d) { return d.id; }))
        .force("charge", d3.forceManyBody())
        .force("center", d3.forceCenter(width / 2, height / 2));

    simulation
        .nodes(nodedata)
        .on("tick", ticked);

    simulation.force("link")
        .links(linkdata);

    simulation.restart();
}

function ticked() {
    link
        .attr("x1", function(d) { return d.source.x; })
        .attr("y1", function(d) { return d.source.y; })
        .attr("x2", function(d) { return d.target.x; })
        .attr("y2", function(d) { return d.target.y; });

    node
        .attr("cx", function(d) { return d.x = Math.max(r, Math.min(width - r, d.x)); })
        .attr("cy", function(d) { return d.y = Math.max(r, Math.min(height - r, d.y)); });
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

    linkdata.push({ source: nodedata[_source], target: nodedata[_target], value: 30 });

    redrawGraph();

    var targetlink = svg.select("#id" + _source.toString() + "_" + _target.toString());
    targetlink.attr("stroke", "#000");
    //targetlink.attr("stroke-opacity", 0.8);
}

function changeNodeColor(id, centerality) {
    var targetnode = svg.select("#id" + id.toString());
    targetnode.attr("fill", color(centerality));
}

function clearAllLinks() {
    svg.selectAll(".link").remove();
    linkdata = [];
    redrawGraph();
}

function clearAllNodeColor() {
    svg.selectAll(".node").attr("fill", color(1));
}

function changeNodeSize(_r) {
    r = _r;
    removeAndRedraw();
}

function changeLinkSize(_stroke) {
    strokewidth = _stroke;
    removeAndRedraw();
}

function resetAll() {
    if (working)
        return;
    r = 1.5;
    strokewidth = 0.5;
    linkdata = [];
    color = d3.scaleOrdinal(d3.schemeCategory20);
    removeAndRedraw();
    // var numberform = document.getElementById("inputnumber");
    // numberform.elements[0].value=numberform.elements[1].value="";
}

function cancelAll() {
    stopflag = true;
}