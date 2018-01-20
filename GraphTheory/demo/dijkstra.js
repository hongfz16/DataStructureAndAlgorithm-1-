var dijkstraApp = {

    dijkstracounter: 0,
    dijkstrasource: 0,
    dijkstratarget: 0,
    filename: ref.allocCString(filmtxtfilename),
    graph_ptr: 0,
    edgeinfo_ptr: 0,
    internal: 10,
    nnum: 0,
    dist_ptr: 0,
    prevarray: 0,

    setTwoNodes: function(id) {
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
    },

    getTwoNodes: function() {
        var numberform = document.getElementById("inputnumber");
        var strfirstnumber = numberform.elements[0].value;
        var strsecondnumber = numberform.elements[1].value;
        if (strfirstnumber === "" || strsecondnumber === "")
            return [-1, -1];
        var firstnum = parseInt(strfirstnumber);
        var secondnum = parseInt(strsecondnumber);
        return [firstnum, secondnum];
    },

    getDijkstraInfo: function() {
        var sourceandtarget = this.getTwoNodes();
        if (sourceandtarget[0] == -1)
            return false;
        for(var i=0;i<2;++i) {
            console.log(sourceandtarget[i]);
            if(sourceandtarget[i]<0 || sourceandtarget[i]>=this.nnum)
                return false;
        }
        this.dijkstratarget = sourceandtarget[1];
        this.dijkstrasource = sourceandtarget[0];
        return true;
    },

    destroyAll: function() {
        graphlib.destroyGraph(this.graph_ptr);
        graphlib.destroyEdgeInfo(this.edgeinfo_ptr);
    },

    revealResult: function(length) {
        var stralert="The length of the shortest way is " + length;
        clearAllLinks();
        var curr = this.dijkstratarget;
        var prev = this.dijkstratarget;
        while (prev != this.dijkstrasource) {
            curr = prev;
            prev = this.prevarray[curr].u;
            if(prev==-1)
            {
                stralert="Cannot find a route";
                break;
            }
            changeLinkColor(prev, curr);
        }
        document.getElementById("dijkstraresult").innerHTML = stralert;
    },

    dijkstraButtonClk: async function() {
        stopflag=false;
        if (working)
            return;
        working = true;

        this.dijkstrasource=this.dijkstratarget=0;
        this.nnum = graphsize;
        this.dist_ptr = new intArray(this.nnum);
        this.prevarray = new edgeinfoArray(this.nnum);
        this.graph_ptr=graphlib.createGraph_s(this.filename);
        this.edgeinfo_ptr=graphlib.createEdgeInfo(0, 0, 0);

        if (!this.getDijkstraInfo())
            return;

        clearAllLinks();

        for (var i = 0; i < this.nnum; ++i) {
            if (stopflag)
            {
                this.destroyAll();
                working=false;
                return;
            }
            if (graphlib.dijkstraStep(this.graph_ptr, i, this.dijkstrasource, this.dist_ptr, this.edgeinfo_ptr, this.prevarray) == -1)
                break;
            changeLinkColor(this.edgeinfo_ptr.deref().u, this.edgeinfo_ptr.deref().v);
            await sleep(this.internal);
        }
        this.revealResult(this.dist_ptr[this.dijkstratarget]);

        working = false;

        this.destroyAll();
        //console.log("here");
    },
}