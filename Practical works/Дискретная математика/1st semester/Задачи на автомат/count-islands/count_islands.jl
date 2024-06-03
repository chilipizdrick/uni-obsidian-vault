using DataStructures

function flood_island!(grid::Matrix{Bool}, i::Int64, j::Int64)::Bool
    directions = ((-1, 0), (1, 0), (0, -1), (0, 1))
    flag = false
    if !grid[i, j]
        flag = true
        queue = Queue{Tuple{Int64,Int64}}()
        enqueue!(queue, (i, j))
        while length(queue) > 0
            (x, y) = dequeue!(queue)
            if !grid[x, y]
                grid[x, y] = true
                for (dx, dy) in directions
                    if 1 <= x + dx <= size(grid, 1) && 1 <= y + dy <= size(grid, 2)
                        enqueue!(queue, (x + dx, y + dy))
                    end
                end
            end
        end
    end
    return flag
end

function count_islands(grid_::Matrix{Bool})::Int64
    grid = grid_
    if length(grid) == 0
        return 0
    end

    cnt = 0

    for i in axes(grid, 1)
        for j in (1, size(grid, 2))
            flood_island!(grid, i, j)
        end
    end
    for i in (1, size(grid, 1))
        for j in axes(grid, 2)
            flood_island!(grid, i, j)
        end
    end

    for i in 2:(size(grid, 1)-1)
        for j in 2:(size(grid, 2)-1)
            if flood_island!(grid, i, j)
                cnt += 1
            end
        end
    end

    return cnt
end


function main()
    function read_matrix()::Matrix{Bool}
        input = read_matrix_string()
        return parse_matrix(input)
    end

    function read_matrix_string()::String
        res = ""
        curr_line = readline()
        while curr_line != ""
            res *= curr_line * "\n"
            curr_line = readline()
        end
        return strip(res)
    end

    function parse_matrix(input::String)
        rows = split(input, "\n")
        m = length(rows)
        n = length(split(rows[1]))
        res = Matrix{Bool}(undef, m, n)
        for i in eachindex(rows)
            columns = map(x -> parse(Bool, x), split(rows[i]))
            for j in eachindex(columns)
                res[i, j] = columns[j]
            end
        end
        return res
    end


    grid1 = Matrix{Bool}(
        [1 1 1 1 1 1 1 0;
            1 0 0 0 0 1 1 0;
            1 0 1 0 1 1 1 0;
            1 0 0 0 0 1 0 1;
            1 1 1 1 1 1 1 0])
    println(count_islands(grid1))

    grid2 = Matrix{Bool}(
        [0 0 1 0 0;
            0 1 0 1 0;
            0 1 1 1 0])
    println(count_islands(grid2))

    println(count_islands(read_matrix()))
end

main()