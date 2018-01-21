var primApp = {
    stepcount: 0,
    nnum: 0,
    filename: ref.allocCString(filmtxtfilename),
    graph_ptr: 0,
    edgeinfo_ptr: 0,
    internal: 10,
    rootid:0,

    getRoot: function() {
        var rootinput=document.getElementById("rootnumber");
        var rootstr=rootinput.elements[0].value;
        for(var i=0;i<rootstr.length;++i)
        {
            if(rootstr[i]>'9' || rootstr[i]<'0') {
                this.root=0;
                alert("Please enter an integer!");
                return false;
            }
        }
        if(rootstr.length==0) {
            this.root=0;
            alert("Please enter an integer!");
            return false;
        }
        this.rootid=parseInt(rootstr);
        console.log(this.rootid);
        return true;
    },

    destroyAll: function() {
        graphlib.destroyGraph(this.graph_ptr);
        graphlib.destroyEdgeInfo(this.edgeinfo_ptr);
    },

    primButtonClk: async function() {
        resetAll();
        stopflag=false;
        if (working)
            return;
        if(!this.getRoot())
            return;
        working = true;
        this.graph_ptr = graphlib.createGraph_s(this.filename);
        this.edgeinfo_ptr = graphlib.createEdgeInfo(0, 0, 0);
        this.nnum = graphsize;

        //clearAllLinks();
        for (var i = 0; i < this.nnum; ++i) {
            if(stopflag)
            {
                this.destroyAll();
                working=false;
                return;
            }
            if(graphlib.primStep(this.graph_ptr, i, this.rootid, this.edgeinfo_ptr)==-1)
                break;
            changeLinkColor(this.edgeinfo_ptr.deref().u, this.edgeinfo_ptr.deref().v)
            //break;
            await sleep(this.internal);
        }
        //console.log("out");
        this.destroyAll();
        working=false;
    },

    primFastButtonClk: async function() {
        resetAll();
        stopflag=false;
        if (working)
            return;
        if(!this.getRoot())
            return;
        working = true;
        this.graph_ptr = graphlib.createGraph_s(this.filename);
        this.edgeinfo_ptr = graphlib.createEdgeInfo(0, 0, 0);
        this.nnum = graphsize;

        var vertexes=[];

        //clearAllLinks();

        for (var i = 0; i < this.nnum; ++i) {
            if(stopflag)
            {
                this.destroyAll();
                working=false;
                return;
            }
            if(graphlib.primStep(this.graph_ptr, i, this.rootid, this.edgeinfo_ptr)==-1)
                break;
            //changeLinkColor(this.edgeinfo_ptr.deref().u, this.edgeinfo_ptr.deref().v)
            linkdata.push({ source: nodedata[this.edgeinfo_ptr.deref().u], target: nodedata[this.edgeinfo_ptr.deref().v], value: 30 })
        }

        redrawGraph();

        //console.log("out");
        this.destroyAll();
        working=false;
    }
}