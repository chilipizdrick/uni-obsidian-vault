using Base

struct Polynomial{T}
    coeffs::Vector{T}

    function Polynomial{T}(a::T) where {T}
        return new{T}(Vector{T}([a]))
    end

    function Polynomial{T}(coeff::Vector{T}) where {T}
        if length(coeff) < 1
            return new{T}(Vector{T}([Base.zero(T)]))
        end

        index = findlast(x -> !Base.iszero(x), coeff)
        if isnothing(index)
            return new{T}(Vector{T}([Base.zero(T)]))
        end

        return new{T}(coeff[begin:index])
    end
end

function copy(p::Polynomial{T})::Polynomial{T} where {T}
    r = Base.copy(p.coeffs)
    return Polynomial{T}(r)
end

function Base.zero(_::Polynomial{T})::Polynomial{T} where {T}
    return Polynomial{T}(Base.zero(T))
end
function Base.zero(::Type{Polynomial{T}})::Polynomial{T} where {T}
    return Polynomial{T}(Base.zero(T))
end

function Base.one(_::Polynomial{T})::Polynomial{T} where {T}
    return Polynomial{T}(Base.one(T))
end
function Base.one(::Type{Polynomial{T}})::Polynomial{T} where {T}
    return Polynomial{T}(Base.one(T))
end

function Base.:(-)(p::Polynomial{T})::Polynomial{T} where {T}
    Polynomial{T}(map(x -> -x, p.coeffs))
end

function Base.:(+)(p::Polynomial{T}, q::Polynomial{T})::Polynomial{T} where {T}
    m = length(p.coeffs)
    n = length(q.coeffs)

    if m > n
        r = copy(p)
        r.coeffs[begin:n] .+= q.coeffs
    else
        r = copy(q)
        r.coeffs[begin:m] .+= p.coeffs
    end

    return Polynomial{T}(r.coeffs)
end

function Base.:(+)(p::Polynomial{T}, a::T)::Polynomial{T} where {T}
    return p + Polynomial{T}([a])
end

function Base.:(+)(a::T, p::Polynomial{T})::Polynomial{T} where {T}
    return p + Polynomial{T}([a])
end

function Base.:(-)(p::Polynomial{T}, q::Polynomial{T})::Polynomial{T} where {T}
    m = length(p.coeffs)
    n = length(q.coeffs)

    if m >= n
        r = copy(p)
        r.coeffs[begin:n] .-= q.coeffs
        return Polynomial{T}(r.coeffs)
    else
        r_coeffs = Base.copy(p.coeffs)
        for _ in (length(p.coeffs)+1):length(q.coeffs)
            push!(r_coeffs, Base.zero(T))
        end
        r_coeffs .-= q.coeffs
        return Polynomial{T}(r_coeffs)
    end
end

function Base.:(-)(p::Polynomial{T}, a::T)::Polynomial{T} where {T}
    return p - Polynomial{T}([a])
end

function Base.:(-)(a::T, p::Polynomial{T})::Polynomial{T} where {T}
    return Polynomial{T}([a]) - p
end

function Base.:(*)(p::Polynomial{T}, q::Polynomial{T})::Polynomial{T} where {T}
    r = Polynomial{T}(Vector{T}())
    for i in eachindex(p.coeffs)
        temp_coeffs = Vector{T}()
        for _ in 1:(i-1)
            append!(temp_coeffs, [Base.zero(T)])
        end
        for j in eachindex(q.coeffs)
            append!(temp_coeffs, [p.coeffs[i] * q.coeffs[j]])
        end
        r = r + Polynomial{T}(temp_coeffs)
    end
    return r
end

function Base.:(*)(p::Polynomial{T}, a::T)::Polynomial{T} where {T}
    new_coeffs = p.coeffs
    for i in eachindex(new_coeffs)
        new_coeffs[i] *= a
    end
    return Polynomial{T}(new_coeffs)
end

function Base.:(*)(a::T, p::Polynomial{T})::Polynomial{T} where {T}
    new_coeffs = p.coeffs
    for i in eachindex(new_coeffs)
        new_coeffs[i] *= a
    end
    return Polynomial{T}(new_coeffs)
end

function Base.divrem(p::Polynomial{T}, q::Polynomial{T})::Tuple{Polynomial{T},Polynomial{T}} where {T}
    if q == Polynomial{T}()
        throw(ErrorException("polynomial division by 0-polynomial"))
    end

    quotent = Polynomial{T}()
    remainder = copy(p)

    while remainder != Polynomial{T}() && ord(remainder) >= ord(q)
        coeffs = Vector{T}()
        power = ord(remainder) - ord(q)
        for _ in 1:power
            push!(coeffs, Base.zero(T))
        end
        push!(coeffs, lead(remainder) / lead(q))
        t = Polynomial{T}(coeffs)

        quotent = quotent + t
        remainder = remainder - t * q
    end

    return (quotent, remainder)
end

function Base.:(/)(p::Polynomial{T}, q::Polynomial{T})::Polynomial{T} where {T}
    return Base.divrem(p, q)[1]
end

function Base.:(/)(p::Polynomial{T}, a::T)::Polynomial{T} where {T}
    new_coeffs = p.coeffs
    for i in eachindex(new_coeffs)
        new_coeffs[i] /= a
    end
    return Polynomial{T}(new_coeffs)
end

# Схема Горнера
function (p::Polynomial{T})(x) where {T}
    if length(p.coeffs) == 1
        return p.coeffs[1]
    end

    res = Base.zero(T)
    for i in lastindex(p.coeffs):-1:1
        res = res * x + p.coeffs[i]
    end

    return res
end

function lagrange_polynomial(points::Vector{Vector{T}})::Polynomial{T} where {T}
    res = zero(Polynomial{T})
    for i in eachindex(points)
        numerator = one(Polynomial{T})
        denominator = one(T)
        for j in eachindex(points)
            if i == j
                continue
            end
            numerator *= Polynomial{T}([-points[j][1], one(T)])
            denominator *= points[i][1] - points[j][1]
        end
        res += points[i][2] * (numerator / denominator)
    end
    return res
end


struct Residue{T,M} <: Number
    value::T

    function Residue{T,M}(value::T) where {T,M}
        return new(Base.mod(value, M))
    end
end

ringmod(::Residue{T,M}) where {T,M} = M
value(a::Residue{T,M}) where {T,M} = a.value
Base.zero(::Type{Residue{T,M}}) where {T,M} = Residue{T,M}(Base.zero(T))
Base.zero(::Residue{T,M}) where {T,M} = Residue{T,M}(Base.zero(T))
Base.one(::Type{Residue{T,M}}) where {T,M} = Residue{T,M}(Base.one(T))
Base.one(::Residue{T,M}) where {T,M} = Residue{T,M}(Base.one(T))
Base.eps(::Type{Residue{T,M}}) where {T,M} = Residue{T,M}(Base.eps(T))
Base.eps(::Residue{T,M}) where {T,M} = Residue{T,M}(Base.eps(T))

Base.:(==)(a::Residue{T,M}, b::Residue{T,M}) where {T,M} = a.value == b.value
Base.:(!=)(a::Residue{T,M}, b::Residue{T,M}) where {T,M} = a.value != b.value
Base.:(<)(a::Residue{T,M}, b::Residue{T,M}) where {T,M} = a.value < b.value
Base.:(>)(a::Residue{T,M}, b::Residue{T,M}) where {T,M} = a.value > b.value
Base.:(<=)(a::Residue{T,M}, b::Residue{T,M}) where {T,M} = a.value <= b.value
Base.:(>=)(a::Residue{T,M}, b::Residue{T,M}) where {T,M} = a.value >= b.value

Base.:(+)(a::Residue{T,M}, b::Residue{T,M}) where {T,M} = Residue{T,M}(a.value + b.value)
Base.:(-)(a::Residue{T,M}, b::Residue{T,M}) where {T,M} = Residue{T,M}(a.value - b.value)
Base.:(-)(a::Residue{T,M}) where {T,M} = Residue{T,M}(-a.value)
Base.:(*)(a::Residue{T,M}, b::Residue{T,M}) where {T,M} = Residue{T,M}(a.value * b.value)
Base.:(^)(a::Residue{T,M}, b::Residue{T,M}) where {T,M} = Residue{T,M}(a.value^b.value)
Base.:(/)(a::Residue{T,M}, b::Residue{T,M}) where {T,M} = a * invmod(b)

function invmod(a::Residue{T,M})::Union{Residue{T,M},Nothing} where {T,M}
    gcd, inverse, _ = gcdx_(a.value, M)
    if gcd != one(a.value)
        return nothing
    end
    return Residue{T,M}(mod(inverse, M))
end

function gcdx_(a::T, b::T)::Tuple{T,T,T} where {T}
    u, v = one(T), zero(T)
    u_, v_ = v, u

    while !iszero(b)
        k, r = divrem(a, b)
        a, b = b, r
        u, u_ = u_, u - k * u_
        v, v_ = v_, v - k * v_
    end
    if a < zero(T)
        a, u, v = -a, -u, -v
    end
    return a, u, v
end