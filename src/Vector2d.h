#ifndef GAME_VECTOR2D_H
#define GAME_VECTOR2D_H

namespace house {

    template <typename T>
    struct Vector2d {
        T x;
        T y;

        T &w;
        T &h;

        constexpr Vector2d() noexcept : x{0}, y{0}, w{x}, h{y} {}
        constexpr Vector2d(T first, T second) noexcept :
            x{first}, y{second}, w{x}, h{y}
        {}
        constexpr Vector2d(const Vector2d<T> &rhs) noexcept :
            x{rhs.x}, y{rhs.y}, w{x}, h{y}
        {}

        constexpr Vector2d<T>& operator= (const Vector2d<T> &rhs) noexcept {
            x = rhs.x;
            y = rhs.y;

            return *this;
        }

        constexpr Vector2d<T> operator+ (const Vector2d<T> &rhs)
        const noexcept
        {
            Vector2d<T> result {
                x + rhs.x,
                y + rhs.y
            };

            return result;
        }
        constexpr Vector2d<T> operator- (const Vector2d<T> &rhs)
        const noexcept
        {
            Vector2d<T> result {
                x - rhs.x,
                y - rhs.y
            };

            return result;
        }
        constexpr Vector2d<T> operator* (const Vector2d<T> &rhs)
        const noexcept
        {
            Vector2d<T> result {
                x * rhs.x,
                y * rhs.y
            };

            return result;
        }

        constexpr Vector2d<T> operator/ (const Vector2d<T> &rhs)
        const noexcept
        {
            Vector2d<T> result {
                x / rhs.x,
                y / rhs.y
            };

            return result;
        }
        constexpr Vector2d<T>& operator+= (const Vector2d<T> &rhs) noexcept {
            *this = *this + rhs;
            
            return *this;
        }
        constexpr Vector2d<T>& operator-= (const Vector2d<T> &rhs) noexcept {
            *this = *this - rhs;

            return *this;
        }
        constexpr Vector2d<T>& operator*= (const Vector2d<T> &rhs) noexcept {
            *this = *this * rhs;

            return *this;
        }
        constexpr Vector2d<T>& operator/= (const Vector2d<T> &rhs) noexcept {
            *this = *this / rhs;

            return *this;
        }
        constexpr bool operator== (const Vector2d<T> &rhs) noexcept {
            return (x == rhs.x && y == rhs.y);
        }
        constexpr bool operator!= (const Vector2d<T> &rhs) noexcept {
            return !(*this == rhs);
        }

        template <typename T2>
        constexpr Vector2d<T>& operator= (const Vector2d<T2> &rhs) {
            x = static_cast<T>(rhs.x);
            y = static_cast<T>(rhs.y);

            return *this;
        }

        template <typename T2>
        constexpr Vector2d<T> operator+ (const Vector2d<T2> &rhs) const {
            Vector2d<T> result {
                static_cast<T>(x + rhs.x),
                static_cast<T>(y + rhs.y)
            };
            
            return result;
        }

        template <typename T2>
        constexpr Vector2d<T> operator- (const Vector2d<T2> &rhs) const {
            Vector2d<T> result {
                static_cast<T>(x - rhs.x),
                static_cast<T>(y -rhs.y)
            };

            return result;
        }

        template <typename T2>
        constexpr Vector2d<T> operator* (const Vector2d<T2> &rhs) const {
            Vector2d<T> result {
                static_cast<T>(x * rhs.x),
                static_cast<T>(y * rhs.y)
            };

            return result;
        }

        template <typename T2>
        constexpr Vector2d<T> operator/ (const Vector2d<T2> &rhs) const {
            Vector2d<T> result {
                static_cast<T>(x / rhs.x),
                static_cast<T>(y / rhs.y)
            };

            return result;
        }

        template <typename T2>
        constexpr Vector2d<T>& operator+= (const Vector2d<T2> &rhs) {
            *this = *this + rhs;

            return *this;
        }

        template <typename T2>
        constexpr Vector2d<T>& operator-= (const Vector2d<T2> &rhs) {
            *this = *this - rhs;
            
            return *this;
        }

        template <typename T2>
        constexpr Vector2d<T>& operator*= (const Vector2d<T2> &rhs) {
            *this = *this * rhs;

            return *this;
        }

        template <typename T2>
        constexpr Vector2d<T>& operator/= (const Vector2d<T2> &rhs) {
            *this = *this / rhs;

            return *this;
        }

        constexpr Vector2d<T>& operator= (T rhs) {
            x = rhs;
            y = rhs;

            return *this;
        }

        constexpr Vector2d<T> operator+ (T rhs) const {
            Vector2d<T> result {
                x + rhs,
                y + rhs
            };

            return result;
        }
        
        constexpr Vector2d<T> operator- (T rhs) const {
            Vector2d<T> result {
                x - rhs,
                y - rhs
            };

            return result;
        }
        
        constexpr Vector2d<T> operator* (T rhs) const {
            Vector2d<T> result {
                x * rhs,
                y * rhs
            };

            return result;
        }
        
        constexpr Vector2d<T> operator/ (T rhs) const {
            Vector2d<T> result {
                x / rhs,
                y / rhs
            };

            return result;
        }

        constexpr Vector2d<T>& operator+= (T rhs) {
            *this = *this + rhs;

            return *this;
        }
        
        constexpr Vector2d<T>& operator-= (T rhs) {
            *this = *this - rhs;

            return *this;
        }
        
        constexpr Vector2d<T>& operator*= (T rhs) {
            *this = *this * rhs;

            return *this;
        }
        
        constexpr Vector2d<T>& operator/= (T rhs) {
            *this = *this / rhs;

            return *this;
        }
        
        template <typename T2>
        constexpr Vector2d<T>& operator= (T2 rhs) {
            x = static_cast<T>(rhs);
            y = static_cast<T>(rhs);

            return *this;
        }

        template <typename T2>
        constexpr Vector2d<T> operator+ (T2 rhs) const {
            Vector2d<T> result {
                static_cast<T>(x + rhs),
                static_cast<T>(y + rhs)
            };

            return result;
        }

        template <typename T2>
        constexpr Vector2d<T> operator- (T2 rhs) const {
            Vector2d<T> result {
                static_cast<T>(x - rhs),
                static_cast<T>(y - rhs)
            };

            return result;
        }

        template <typename T2>
        constexpr Vector2d<T> operator* (T2 rhs) const {
            Vector2d<T> result {
                static_cast<T>(x * rhs),
                static_cast<T>(y * rhs)
            };

            return result;
        }

        template <typename T2>
        constexpr Vector2d<T> operator/ (T2 rhs) const {
            Vector2d<T> result {
                static_cast<T>(x / rhs),
                static_cast<T>(y /rhs)
            };

            return result;
        }

        template <typename T2>
        constexpr Vector2d<T>& operator+= (T2 rhs) {
            *this = *this + rhs;

            return *this;
        }

        template <typename T2>
        constexpr Vector2d<T>& operator-= (T2 rhs) {
            *this = *this - rhs;

            return *this;
        }

        template <typename T2>
        constexpr Vector2d<T>& operator*= (T2 rhs) {
            *this = *this * rhs;

            return *this;
        }

        template <typename T2>
        constexpr Vector2d<T>& operator/= (T2 rhs) {
            *this = *this / rhs;

            return *this;
        }

        template <typename T2>
        constexpr bool operator== (const Vector2d<T2> &rhs) noexcept {
            return (*this == static_cast<Vector2d<T>>(rhs));
        }

        template <typename T2>
        constexpr bool operator!= (const Vector2d<T2> &rhs) noexcept {
            return {*this != static_cast<Vector2d<T>>(rhs)};
        }

        constexpr Vector2d<T> operator- () const {
            Vector2d<T> result {*this * -1};

            return result;
        }


        template <typename T2>
        constexpr operator Vector2d<T2> () {
            Vector2d<T2> result {
                static_cast<T2>(this->x), 
                static_cast<T2>(this->y)
            };

            return result;
        }

        constexpr Vector2d<T> abs() {
            x = std::abs(x);
            y = std::abs(y);

            return *this;
        }

        static constexpr Vector2d<T> abs(const Vector2d<T> &vec) {
            Vector2d<T> temp{vec};
            temp.abs();

            return temp;
        }
    };

} // namespace house

#endif // !GAME_VECTOR2D_H