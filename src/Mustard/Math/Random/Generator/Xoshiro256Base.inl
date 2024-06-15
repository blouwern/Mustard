namespace Mustard::Math::Random::inline Generator {

template<typename ADerived>
constexpr Xoshiro256Base<ADerived>::Xoshiro256Base() : // clang-format off
    XoshiroBase<ADerived, 256>{{0x893C3E22C678FAA9ull,
                                0x30589ADC78696ADAull,
                                0x1D541511D5F51D5Bull,
                                0xE3CBD397A993A9EEull}} { // clang-format on
    static_assert(std::derived_from<ADerived, Xoshiro256Base<ADerived>>);
}

template<typename ADerived>
constexpr Xoshiro256Base<ADerived>::Xoshiro256Base(std::uint64_t seed) :
    XoshiroBase<ADerived, 256>{seed} {}

template<typename ADerived>
MUSTARD_ALWAYS_INLINE constexpr auto Xoshiro256Base<ADerived>::Step() -> void {
    const auto t{this->fState[1] << 17};

    this->fState[2] ^= this->fState[0];
    this->fState[3] ^= this->fState[1];
    this->fState[1] ^= this->fState[2];
    this->fState[0] ^= this->fState[3];

    this->fState[2] ^= t;

    this->fState[3] = std::rotl(this->fState[3], 45);
}

template<typename ADerived>
template<Concept::Character AChar>
auto Xoshiro256Base<ADerived>::StreamOutput(std::basic_ostream<AChar>& os) const -> decltype(os) {
    return os << this->fState[0] << ' '
              << this->fState[1] << ' '
              << this->fState[2] << ' '
              << this->fState[3];
}

template<typename ADerived>
template<Concept::Character AChar>
auto Xoshiro256Base<ADerived>::StreamInput(std::basic_istream<AChar>& is) & -> decltype(is) {
    return is >> this->fState[0] // clang-format off
              >> this->fState[1]
              >> this->fState[2]
              >> this->fState[3]; // clang-format on
}

} // namespace Mustard::Math::Random::inline Generator
