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
    'closenesscentrality': [ref.types.void, [graphinfoptr,intArray]],
    'connectivityQuery': [ref.types.bool, [graphinfoptr,'int','int','int']],
    'connectivityInit': [ref.types.void, [graphinfoptr]]
});