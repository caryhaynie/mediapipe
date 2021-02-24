""" Embed a MediaPipe graph as code, reducing external dependencies

"""

load("//mediapipe/framework/tool:mediapipe_graph.bzl", "data_as_c_string", "mediapipe_binary_graph")
load("//mediapipe/framework/deps:expand_template.bzl", "expand_template")
load("//mediapipe/framework/tool:build_defs.bzl", "clean_dep")

def mediapipe_embed_graph(
        name,
        register_as,
        graph,
        deps = [],
        visibility = None,
        testonly = None,
        **kwargs):
    """Defines a registered subgraph for inclusion in other graphs.

    Args:
        name: name of the subgraph target to define.
        register_as: name used to invoke this graph in supergraphs. Should be in
            CamelCase.
        graph: the BUILD label of a text-format MediaPipe graph.
        deps: any calculators or subgraphs used by this graph.
        visibility: The list of packages the subgraph should be visible to.
        testonly: pass 1 if the graph is to be used only for tests.
        **kwargs: Remaining keyword args, forwarded to cc_library.
    """
    graph_base_name = name
    mediapipe_binary_graph(
        name = name + "_graph",
        graph = graph,
        output_name = graph_base_name + ".binarypb",
        deps = deps,
        testonly = testonly,
    )
    data_as_c_string(
        name = name + "_inc",
        srcs = [graph_base_name + ".binarypb"],
        outs = [graph_base_name + ".inc"],
    )

    # cc_library for a linked mediapipe graph.
    expand_template(
        name = name + "_linked_cc",
        template = clean_dep("//mediapipe/examples/unity:embedded_graph_template.cc"),
        out = name + "_linked.cc",
        substitutions = {
            "{{SUBGRAPH_CLASS_NAME}}": register_as,
            "{{SUBGRAPH_INC_FILE_PATH}}": native.package_name() + "/" + graph_base_name + ".inc",
        },
        testonly = testonly,
    )
    native.cc_library(
        name = name,
        srcs = [
            name + "_linked.cc",
            graph_base_name + ".inc",
        ],
        deps = [
            clean_dep("//mediapipe/framework:calculator_framework"),
        ] + deps,
        alwayslink = 1,
        visibility = visibility,
        testonly = testonly,
        **kwargs
    )