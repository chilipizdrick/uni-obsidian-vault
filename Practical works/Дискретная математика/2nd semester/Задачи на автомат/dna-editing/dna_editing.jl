using DataStructures

struct Node
    value::String

    function Node(val::String)
        return new(val)
    end
end

struct Transition
    from::String
    to::String
    prob::Float64
end

struct IndexedTransition
    from::String
    to::String
    prob::Float64
    idx::Int64

    function IndexedTransition(from_node::Node, to_node::Node, transitions::Vector{Transition})
        index = 0
        for i in eachindex(from_node.value)
            if string(from_node.value[i]) != string(to_node.value[i])
                index = i
            end
        end
        transition = get_transition(from_node, to_node, transitions)
        return new(transition.from, transition.to, transition.prob, index)
    end
end

str_sub(str1, str2, idx) = @. SubString(str1, 1, idx - 1) * str2 * SubString(str1, idx + 1, length(str1))

function compose_transitions(froms::Vector{String}, tos::Vector{String}, probs::Vector{Float64})::Vector{Transition}
    res = Vector{Transition}()
    for i in eachindex(froms)
        push!(res, Transition(froms[i], tos[i], probs[i]))
    end
    return res
end

function get_neighbors(node::Node, transitions::Vector{Transition})::Vector{Node}
    neighbors = Vector{Node}()
    for transition in transitions
        for i in eachindex(node.value)
            if transition.from == string(node.value[i])
                neighbor = Node(str_sub(node.value, transition.to, i))
                push!(neighbors, neighbor)
            end
        end
    end
    return neighbors
end

function get_max_node(nodes::Vector{Node}, f_score::Dict{Node})::Node
    curr_node = nodes[1]
    for i in 2:length(nodes)
        if !isnothing(f_score[curr_node]) && !isnothing(f_score[nodes[i]]) && f_score[nodes[i]] > f_score[curr_node]
            curr_node = nodes[i]
        end
    end
    return curr_node
end

function get_transition(from_node::Node, to_node::Node, transitions::Vector{Transition})::Transition
    from_char, to_char = "", ""
    for i in eachindex(from_node.value)
        if string(from_node.value[i]) != string(to_node.value[i])
            from_char, to_char = string(from_node.value[i]), string(to_node.value[i])
            break
        end
    end
    for transition in transitions
        if transition.from == from_char && transition.to == to_char
            return transition
        end
    end
end

function edge_weight(from_node::Node, to_node::Node, transitions::Vector{Transition})::Float64
    return get_transition(from_node, to_node, transitions).prob
end

function reconstruct_path(came_from::Dict{Node,Node}, curr_node_::Node, transitions::Vector{Transition})::Vector{IndexedTransition}
    curr_node = curr_node_
    node_path = Vector{Node}([curr_node])
    while curr_node in keys(came_from)
        curr_node = came_from[curr_node]
        push!(node_path, curr_node)
    end
    reverse!(node_path)

    transition_path = Vector{IndexedTransition}()
    prev_node = node_path[1]
    for i in 2:length(node_path)
        curr_node = node_path[i]
        push!(transition_path, IndexedTransition(prev_node, curr_node, transitions))
        prev_node = curr_node
    end

    return transition_path
end

function inverse_a_star(start::String, target::String, transitions::Vector{Transition}; h::Function=x -> 1.0)::Vector{IndexedTransition}
    start_node = Node(start)
    queued_nodes = Vector{Node}([start_node])
    came_from = Dict{Node,Node}()
    g_score = Dict{Node,Float64}(start_node => 1.0)
    f_score = Dict{Node,Float64}()
    f_score[start_node] = g_score[start_node] * h(start_node.value)

    while length(queued_nodes) > 0
        curr_node = get_max_node(queued_nodes, f_score)
        if curr_node == Node(target)
            return reconstruct_path(came_from, curr_node, transitions)
        end

        # Remove processed node from queue
        filter!(x -> x != curr_node, queued_nodes)

        neighbors = get_neighbors(curr_node, transitions)
        for neighbor in neighbors
            tentative_g_score = get(g_score, curr_node, 0) * edge_weight(curr_node, neighbor, transitions)
            if tentative_g_score > get(g_score, neighbor, 0)
                came_from[neighbor] = curr_node

                g_score[neighbor] = tentative_g_score
                f_score[neighbor] = tentative_g_score * h(neighbor.value)
                if !(neighbor in queued_nodes)
                    push!(queued_nodes, neighbor)
                end
            end
        end
    end
end

function print_path(transitions::Vector{IndexedTransition})::Nothing
    for transition in transitions
        println("at idx=$(transition.idx): \'$(transition.from)\' -> \'$(transition.to)\' with P = $(transition.prob)")
    end
    total_prob = reduce(*, [x.prob for x in transitions])
    println("TOTAL P = $(total_prob)")
end


function main()
    source = "abcd"
    target = "acbe"
    from = ["a", "b", "c", "c", "e", "d"]
    to = ["b", "c", "b", "e", "b", "e"]
    p = [0.9, 0.8, 0.8, 0.95, 0.9, 0.7]

    transitions = compose_transitions(from, to, p)
    println("--- $(source) -> $(target) ---")
    print_path(inverse_a_star(source, target, transitions))

    function read_vector(T::Type)::Vector
        return Vector{T}(map(x -> parse(T, x), split(strip(readline()))))
    end

    print("source = ")
    source = String(strip(readline()))
    print("target = ")
    target = String(strip(readline()))
    print("from = ")
    from = Vector{String}(split(strip(readline())))
    print("to = ")
    to = Vector{String}(split(strip(readline())))
    print("p = ")
    p = Vector{Float64}(read_vector(Float64))

    transitions = compose_transitions(from, to, p)
    println("--- $(source) -> $(target) ---")
    print_path(inverse_a_star(source, target, transitions))
end

main()