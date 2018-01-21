var connectivityApp = {
    filename: ref.allocCString(filmtxtfilename),
    graph_ptr: 0,
    queryid: -1,
    connectivecount: 0,
    nnum: 0,
    connectivenodedata: [],
    connectivenodeinfo: [],
    //color: d3.scaleOrdinal(d3.schemeCategory20),
    ST: 15,
    _node: 0,
    groups: [],
    nodePadding: 2,
    _simulation: 0,
    oldquery: -1,
    initialized: false,

    isNum: function(str) {
        for (var i = 0; i < str.length; ++i) {
            if (str[i] > '9' || str[i] < '0')
                return false;
        }
        return true;
    },

    getData: function() {
        var tsform = document.getElementById("TSnumber");
        var ststr = tsform.elements[0].value;
        var qidstr = tsform.elements[1].value;
        if (this.isNum(ststr))
            this.ST = parseInt(ststr);
        else {
            alert("Please enter an interger!");
            return false;
        }
        if (this.isNum(qidstr))
            this.queryid = parseInt(qidstr);
        else {
            alert("Please enter an interger!");
            return false;
        }
        return true;
    },

    initGraph: function() {
        if (this.initialized) {
            alert("Do not repeatly initialize!");
            return;
        }
        if (!this.getData())
            return;
        this.graph_ptr = graphlib.createGraph_s(this.filename);
        graphlib.connectivityInit(this.graph_ptr);
        this.initialized = true;
        this.nnum = graphsize;
        this.drawGraph();
    },

    destroyAll: function() {
        graphlib.destroyGraph(this.graph_ptr);
    },

    drawGraph: function() {
        if (!this.getData())
            return;

        svg.selectAll("circle").remove();

        this.groups = [];
        this.connectivenodedata = [];
        this.connectivenodeinfo = [];

        for (var i = 0; i < this.nnum; ++i) {
            var igroup = graphlib.connectivityRep(this.graph_ptr, i, this.ST);
            this.connectivenodeinfo.push({
                id: i.toString(),
                group: igroup
            });
            var findresult = this.groups.findIndex((value, index, arr) => {
                return value == igroup;
            });
            if (findresult == -1) {
                this.groups.push(igroup);
                this.connectivenodedata.push({
                    id: this.groups.length - 1,
                    radius: 1
                });
            } else {
                this.connectivenodedata[findresult].radius++;
            }
        }

        //console.log(graphlib.connectivityCount(this.graph_ptr,this.ST));

        var max = 0;
        for (var i = 0; i < this.connectivenodedata.length; ++i) {
            if (max < this.connectivenodedata[i].radius)
                max = this.connectivenodedata[i].radius;
        }

        for (var i = 0; i < this.connectivenodedata.length; ++i) {
            this.connectivenodedata[i].radius = Math.sqrt(this.connectivenodedata[i].radius); //Math.floor(this.connectivenodedata[i].radius/max*30);
            if (this.connectivenodedata[i].radius <= 2)
                this.connectivenodedata[i].radius = 3;
        }
        simulation.stop();
        simulation = d3.forceSimulation()
            .force("forceX", d3.forceX().strength(.25).x(width * .5))
            .force("forceY", d3.forceY().strength(.25).y(height * .5))
            .force("center", d3.forceCenter().x(width * .5).y(height * .5))
            .force("charge", d3.forceManyBody().strength(-15));

        simulation
            .nodes(this.connectivenodedata)
            //.force("collide", d3.forceCollide().strength(.9).radius(function(d) { return d.radius + this.nodePadding; }).iterations(1))
            .on("tick", this.ticked);

        svg.selectAll(".node").remove();
        svg.selectAll(".link").remove();

        node = svg.selectAll("circle")
            .data(this.connectivenodedata)
            .enter().append("circle")
            .attr("id", function(d) { return "id" + d.id.toString(); })
            .attr("r", function(d) { return d.radius; })
            .attr("fill", function(d) { return color(1); })
            .attr("cx", function(d) { return d.x; })
            .attr("cy", function(d) { return d.y; })
            .call(d3.drag()
                .on("start", dragstarted)
                .on("drag", dragged)
                .on("end", dragended));


        // node.on("click",function(d) {
        //  var infostr="";
        //  for(var i =0;i<graphsize;++i) {
        //      if(this.connectivenodeinfo[i].group==this.groups[d.id])
        //          str+=("id:"+i.toString()+"<br>name:"+"<br><br>");
        //  }
        //  showinfo(infostr);
        //  //console.log("onclick");
        // });
        //this._node = this.svg.selectAll("circle");

        simulation.restart();
    },

    ticked: function(d) {
        node
            .attr("cx", function(d) { return d.x; })
            .attr("cy", function(d) { return d.y; })

    },

    changeNodeColor: function(id, colorstr) {
        var targetnode = svg.select("#id" + id.toString());
        targetnode.attr("fill", colorstr);
    },

    query: function(id) {
        var igroup = graphlib.connectivityRep(this.graph_ptr, id, this.ST);
        id = this.groups.findIndex((value, index, arr) => {
            return value == igroup;
        });
        if (this.oldquery != -1) {
            this.changeNodeColor(this.oldquery, color(1));
        }
        this.oldquery = id;
        this.changeNodeColor(id, "rgb(255,0,0)");
    },

    queryNode: function() {
        if (!this.getData())
            return;
        if (this.queryid == -1)
            return;
        this.query(this.queryid);
    }

};

var connectivityReApp = {
    filename: ref.allocCString(filmtxtfilename),
    graph_ptr: 0,
    edgeinfo_ptr:0,
    queryid: -1,
    connectivecount: 0,
    nnum: 0,
    vnum: 0,
    connectivenodedata: [],
    connectivenodeinfo: [],
    //color: d3.scaleOrdinal(d3.schemeCategory20),
    ST: 15,
    _node: 0,
    groups: [],
    nodePadding: 2,
    _simulation: 0,
    oldquery: -1,
    initialized: false,
    edgearray: 0,

    isNum: function(str) {
        for (var i = 0; i < str.length; ++i) {
            if (str[i] > '9' || str[i] < '0')
                return false;
        }
        return true;
    },

    getData: function() {
        var tsform = document.getElementById("TSRenumber");
        var ststr = tsform.elements[0].value;
        if (this.isNum(ststr))
            this.ST = parseInt(ststr);
        else {
            alert("Please enter an interger!");
            return false;
        }
        return true;
    },

    initGraph: function() {
        resetAll();
        if (this.initialized) {
            alert("Do not repeatly initialize!");
            return;
        }
        if (!this.getData())
            return;
        this.graph_ptr = graphlib.createGraph_s(this.filename);
        //graphlib.connectivityInit(this.graph_ptr);
        this.initialized = true;
        this.nnum = graphsize;
        this.vnum = vsize;
        //console.log(this.vnum);
        this.drawGraph();
    },

    destroyAll: function() {
        graphlib.destroyGraph(this.graph_ptr);
    },

    drawGraph: function() {
        resetAll();
        if (!this.getData())
            return;
        //this.edgearray = new edgeinfoArray(2*this.vnum);
        //console.log(this.edgearray.length);
        //var itenum = graphlib.getEdges(this.graph_ptr, this.edgearray, this.ST);
        // console.log(itenum);
        //simulation.stop();
        // for (var i = 0; i < itenum; ++i) {
        //     linkdata.push({
        //         source: nodedata[this.edgearray[i].u],
        //         target: nodedata[this.edgearray[i].v],
        //         value: 30
        //     });
        // }
        this.edgeinfo_ptr = graphlib.createEdgeInfo(0, 0, 0);
        for (var i = 0; i < this.nnum - 1; ++i) {
            if (stopflag)
            {
                this.destroyAll();
                working=false;
                return;
            }
            if(!graphlib.kruskalStep(this.graph_ptr, i, this.edgeinfo_ptr,this.ST))
                break;
            //changeLinkColor(this.edgeinfo_ptr.deref().u, this.edgeinfo_ptr.deref().v);
            //await sleep(this.internal);
            linkdata.push({ source: nodedata[this.edgeinfo_ptr.deref().u], target: nodedata[this.edgeinfo_ptr.deref().v], value: 30 })
        }
        redrawGraph();
        //simulation.restart();
    }
}