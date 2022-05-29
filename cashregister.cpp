#include <vector>
#include <algorithm>
#include <numeric>
#include <string.h>
#include <string>
#include <iostream>
#include <iomanip>

class CashRegister
{
    private:
        // Data structure for coupons, contains coupon ID and percent of discount that is given when applied.
        struct Coupon {
            std::string id;
            float percentDiscount;
        };

        // Defines the cart vectors and coupons vector.
        std::vector<double> currentCart, salesCart;
        std::vector<Coupon> coupons;

    public:
        // VARIABLE ACCESSORS //

        /**
            Gets the size of the current sale's cart.
            @return int currentCartSize
        */
        int getItemCount(void)
        {
            return this -> currentCart.size();
        }

        /**
            Gets the number of sales sanctioned that day.
            @return int salesCartSize
        */
        int getSalesCount(void)
        {
            return this -> salesCart.size();
        }

        /**
            Gets the total amount of cash from sales for the day.
            @return double salesCartSize
        */
        double getSalesTotal(void)
        {
            return std::accumulate(this -> salesCart.begin(), this -> salesCart.end(), 0.0);
        }

        /**
            Gets the total amount of cash due for the current sale.
            @return currentCartAmount
        */
        double getCurrentTotal(void)
        {
            return std::accumulate(this -> currentCart.begin(), this -> currentCart.end(), 0.0);
        }



        // ITEM FUNCTIONS / CART MUTATORS //

        /**
            Clears all items from the current cart.
            @return void
        */
        void clearItems(void)
        {
            this -> currentCart.clear();
        }

        /**
            Clears statistics for the sales of that day.
            @return void
        */
        void resetSales(void)
        {
            this -> salesCart.clear();
        }


        /**
            Adds one item to the current sale's cart.
            @param int price The price of the item.
            @param std::string couponID Optional argument if you want to apply a coupon code.
            @return void
        */
        void addItem(int price, std::string couponID = "")
        {
            if (price <= 0) return; // Guard clause so we aren't adding invalid data to our system.

            double charged = price;

            if (couponID != "") // If optional Coupon Code parameter was filled.
            {
                double discountPercent = this -> getCouponDiscount(couponID);

                if (discountPercent > 0)
                {
                    double amountSaved = (charged * discountPercent);
                    charged -= amountSaved;
                    std::cout << std::setprecision(2) << std::fixed << "[*] Applied coupon code: " << couponID << std::endl << "[*] Initial price: $" << charged + amountSaved << std::endl << "[*] Saved: $" << amountSaved << std::endl << "[*] New price: $" << charged << std::endl;
                }
                else
                {
                    std::cout << "Invalid coupon code: " << couponID << std::endl;
                }
            }

            this -> currentCart.push_back(price);
            this -> salesCart.push_back(price);
        }

        /**
            Adds one or more items to the current sale's cart.
            @param int price The price of the item.
            @param int quantity The amount of the item you are purchasing.
            @param std::string couponID Optional argument if you want to apply a coupon code.
        */
        void addItems(int price, int quantity, std::string couponID = "")
        {
            if (price <= 0 || quantity <= 0) return; // Guard clause so we aren't adding invalid data to our system.

            double charged = (price * quantity);

            if (couponID != "") // If optional Coupon Code parameter was filled.
            {
                double discountPercent = this -> getCouponDiscount(couponID);

                if (discountPercent > 0)
                {
                    double amountSaved = (charged * discountPercent);
                    charged -= amountSaved;
                    
                    std::cout << std::setprecision(2) << std::fixed << "[*] Applied coupon code: " << couponID << std::endl << "[*] Initial price: $" << charged + amountSaved << std::endl << "[*] Saved: $" << amountSaved << std::endl << "[*] New price: $" << charged << std::endl;
                }
                else
                {
                    std::cout << "[*] Invalid coupon code: " << couponID << std::endl;
                }
            }

            this -> currentCart.push_back(charged);
            this -> salesCart.push_back(charged);
        }



        // MISC FUNCTIONS / CONSOLE FUNCTIONS //

        /**
            Prints out all items in the current sale's cart.
            @return void
        */
        void displayAll(void)
        {
            int position = 0;
            for(double item : this -> currentCart)
            {
               position++;
               std::cout << std::setprecision(2) << std::fixed << "[*] Item " << position << ": $" << item << std::endl;
            }
        }

        /**
            Prints out all items sold that day.
            @return void
        */
        void listSales(void)
        {
            int position = 0;
            for (double item : this -> salesCart)
            {
                position++;
                std::cout << std::setprecision(2) << std::fixed << "[*] Item " << position << ": $" << item << std::endl;
            }
        }



        // COUPON FUNCTIONS / COUPON MUTATORS //

        /**
            Adds a coupon to the list of valid coupon codes.
            @param std::string couponID The ID of the coupon (coupon code).
            @param float couponPercentDiscount The percentage of discount given to the user. (Must be in decimal form | ex: 10% -> 0.1)
            @return void
        */
        void addCoupon(std::string couponID, float couponPercentDiscount)
        {
            if(couponPercentDiscount <= 0)
            {
                std::cout << "[*] Coupon Discounts must be greater than 0!" << std::endl;
                return;
            }

            Coupon newCoupon;

            newCoupon.id = couponID;
            newCoupon.percentDiscount = couponPercentDiscount;

            this -> coupons.push_back(newCoupon);
        }

        /**
            Removes coupon from the list of valid coupon codes.
            @param std::string couponID The ID of the coupon (coupon code).
            @return void
        */
        void removeCoupon(std::string couponID)
        {
            std::remove_if(this -> coupons.begin(), this -> coupons.end(), [&](Coupon currentCoupon) {
                return (currentCoupon.id == couponID);
            });
        }

        /**
            Removes all coupons from the list of valid coupon codes.
            @return void
        */
        void clearCoupons(void)
        {
            this -> coupons.clear();
        }

        /**
            Gets percent discount from entered coupon ID (coupon code).
            @param std::string couponID The ID of the coupon (coupon code).
            @return float discountPercent
        */
        float getCouponDiscount(std::string couponID)
        {
            bool isValid = false;
            float discountPercent;

            for (Coupon coupon : this -> coupons)
            {
                if (coupon.id == couponID)
                {
                    isValid = true;
                    discountPercent = coupon.percentDiscount;
                    break;
                }
            }

            if (isValid)
            {
                return discountPercent;
            }
            else
            {
                return 0;
            }
        }
};
