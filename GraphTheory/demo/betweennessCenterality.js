var betweenCenteralityApp = {
    nnum: 0,
    filename: ref.allocCString(filmtxtfilename),
    graph_ptr:0,
    nodeCenteralityArray:0,

    destroyAll: function() {
        graphlib.destroyGraph(this.graph_ptr);
    },

    betweennessCenteralityButtonClk: async function() {
        resetAll();
    	if(working)
    		return;
    	working=true;
        this.nnum = graphsize;
        this.graph_ptr = graphlib.createGraph_s(this.filename);
        this.nodeCenteralityArray = new intArray(this.nnum);
        graphlib.betweennessCentrality(this.graph_ptr, this.nodeCenteralityArray);
        var max = 0;
        var min = 99999;
        for (var i = 0; i < this.nnum; ++i) {
            if (this.nodeCenteralityArray[i] > max)
                max = this.nodeCenteralityArray[i];
            if (this.nodeCenteralityArray[i] < min)
                min = this.nodeCenteralityArray[i];
        }
        color = d3.scaleLinear().domain([min, max])
            .interpolate(d3.interpolateHcl)
            .range([d3.rgb("#007AFF"), d3.rgb('#FFF500')]);

        for (var i = 0; i < this.nnum; ++i) {
            changeNodeColor(i, this.nodeCenteralityArray[i]);
        }
        this.destroyAll();
        working=false;
    }
}