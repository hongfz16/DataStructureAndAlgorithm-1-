var kruskalApp = {
    nnum: 0,
    filename: ref.allocCString(filmtxtfilename),
    graph_ptr: 0,
    edgeinfo_ptr: 0,
    internal:10,

    destroyAll: function() {
        graphlib.destroyGraph(this.graph_ptr);
        graphlib.destroyEdgeInfo(this.edgeinfo_ptr);
    },

    kruskalButtonClk: async function() {
        resetAll();
        stopflag=false;
        if(working)
        	return;
        working=true;
        this.nnum = graphsize;
        //clearAllLinks();
        this.graph_ptr = graphlib.createGraph_s(this.filename);
        this.edgeinfo_ptr = graphlib.createEdgeInfo(0, 0, 0);
        for (var i = 0; i < this.nnum - 1; ++i) {
        	if (stopflag)
            {
                this.destroyAll();
                working=false;
                return;
            }
            if(!graphlib.kruskalStep(this.graph_ptr, i, this.edgeinfo_ptr))
            	break;
            changeLinkColor(this.edgeinfo_ptr.deref().u, this.edgeinfo_ptr.deref().v);
            await sleep(this.internal);
        }
        this.destroyAll();
        //console.log("here");
        working=false;
    },
    kruskalFastButtonClk: async function() {
        resetAll();
        stopflag=false;
        if(working)
            return;
        working=true;
        this.nnum = graphsize;
        //clearAllLinks();
        this.graph_ptr = graphlib.createGraph_s(this.filename);
        this.edgeinfo_ptr = graphlib.createEdgeInfo(0, 0, 0);
        for (var i = 0; i < this.nnum - 1; ++i) {
            if (stopflag)
            {
                this.destroyAll();
                working=false;
                return;
            }
            if(!graphlib.kruskalStep(this.graph_ptr, i, this.edgeinfo_ptr))
                break;
            //changeLinkColor(this.edgeinfo_ptr.deref().u, this.edgeinfo_ptr.deref().v);
            //await sleep(this.internal);
            linkdata.push({ source: nodedata[this.edgeinfo_ptr.deref().u], target: nodedata[this.edgeinfo_ptr.deref().v], value: 30 })
        }
        this.destroyAll();
        redrawGraph();
        //console.log("here");
        working=false;
    }
}