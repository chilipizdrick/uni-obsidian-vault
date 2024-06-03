include("./lib.jl")


function main()
    p = 13
    x = Residue{Int64,p}(4)
    q = Polynomial{Residue{Int64,p}}(
        map(x -> Residue{Int64,p}(x), [1, 2, 3, 4, 2, 1]))
    println(value(q(x)))

    print("p = ")
    p = parse(Int64, strip(readline()))
    print("x = ")
    x = Residue{Int64,p}(parse(Int64, strip(readline())))
    print("q(x) = ")
    q = Polynomial{Residue{Int64,p}}(map(x -> Residue{Int64,p}(parse(Int64, x)), split(strip(readline()), " ")))
    println(value(q(x)))
end

main()