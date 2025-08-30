include("./lib.jl")


function main()
    function parse_points(input::String, p::Int64)
        nums = split(strip(input))
        @assert(length(nums) % 2 == 0)
        res = Vector{Vector{Residue{Int64,p}}}()
        for i in eachindex(nums)
            if (i % 2 == 0)
                continue
            end
            push!(res, Vector{Residue{Int64,p}}(
                map(x -> Residue{Int64,p}(parse(Int64, x)), [nums[i], nums[i+1]])))
        end
        return res
    end


    p = 17
    x = Residue{Int64,p}(14)
    points = parse_points("""
        0 2
        1 4
        2 1
        6 2
    """, p)
    q = lagrange_polynomial(points)
    println(value(q(x)))

    print("p = ")
    p = parse(Int64, strip(readline()))
    print("x = ")
    x = Residue{Int64,p}(parse(Int64, strip(readline())))
    print("[(x,y)] = ")
    points = parse_points(readline(), p)
    q = lagrange_polynomial(points)
    println(value(q(x)))
end

main()
