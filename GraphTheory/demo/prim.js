var primApp = {
    stepcount: 0,
    nnum: 0,
    filename: ref.allocCString(randomtxtfilename),
    graph_ptr: 0,
    edgeinfo_ptr: 0,
    internal: 10,

    destroyAll: function() {
        graphlib.destroyGraph(this.graph_ptr);
        graphlib.destroyEdgeInfo(this.edgeinfo_ptr);
    },

    primButtonClk: async function() {
        stopflag=false;
        if (working)
            return;
        working = true;
        this.graph_ptr = graphlib.createGraph_s(this.filename);
        this.edgeinfo_ptr = graphlib.createEdgeInfo(0, 0, 0);
        this.nnum = graphsize;

        clearAllLinks();
        for (var i = 0; i < this.nnum; ++i) {
            if(stopflag)
            {
                this.destroyAll();
                working=false;
                return;
            }
            if(graphlib.primStep(this.graph_ptr, i, 0, this.edgeinfo_ptr)==-1)
                break;
            changeLinkColor(this.edgeinfo_ptr.deref().u, this.edgeinfo_ptr.deref().v)
            //break;
            await sleep(this.internal);
        }
        //console.log("out");
        this.destroyAll();
        working=false;
    }
}