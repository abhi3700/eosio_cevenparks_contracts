#pragma once
#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>
#include <eosio/system.hpp>
// #include <eosio/crypto.hpp>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>		// for strtoull
#include <algorithm>			// for std::find_if
// #include <regex>



using eosio::contract;
using eosio::print;
using eosio::name;
using eosio::multi_index;
using eosio::const_mem_fun;
using eosio::indexed_by;
using eosio::asset;
using eosio::check;
using eosio::permission_level;
using eosio::datastream;
using eosio::current_time_point;
using eosio::action;
using eosio::same_payer;
using eosio::symbol;
using eosio::extended_symbol;
// using eosio::require_recipient;
using eosio::checksum256;
// using eosio::action_wrapper;

using std::string;
using std::vector;
using std::map;
using std::make_pair;
using std::count;
// using std::regex;

CONTRACT cevenparksio : public contract {
public:
	using contract::contract;


	/**
	 * @brief - deposit money to the contract ac
	 * @details - deposit money to the contract ac with memo - telegram user_id e.g. 452435325
	 * 			- accepts any token i.e. EOSIO token e.g. "EOS", "TOE", "FUTBOL" created on a chain
	 * @param from - user account
	 * @param contract_ac - contract ac
	 * @param quantity - in eosio tokens - EOS, TOE, etc.
	 * @param memo - purpose which should include telegram user_id
	 */
	[[eosio::on_notify("eosio.token::transfer")]]
	void depositfund( const name& from_ac, 
						const name& contract_ac, 
						const asset& quantity,
						const string& memo 
						);

	/**
	 * @brief - withdraw amount
	 * @details - withdraw amount from_ac to to_ac
	 * 
	 * @param from_ac - from eosio account
	 * @param from_username - from telegram username
	 * @param to_ac - to eosio account
	 * @param quantity - qty
	 * @param memo - memo
	 */
	// void withdrawfund( const name& from_ac,
	// 					 const name& to_ac,
	// 					 const asset& quantity,
	// 					 const string& memo 
	// 					);

	/**
	 * @brief - sign up or register for new user
	 * @details - sign up or register for new user
	 * 
	 * @param username - username
	 * @param email_id - email id
	 * @param password - password
	 * 
	 * @pre - password hash
	 */
	ACTION signup( const name& username,
					string email_id,
					checksum256 password_hash
					);


	/**
	 * @brief - login in/out
	 * @details - login in/out
	 * 
	 * @param username - username
	 * @param is_logged_in - is logged in
	 * 
	 * @pre - username must exist
	 * @pre - password hash should match with the stored one
	 */
	ACTION login( const name& username,
					checksum256 password_hash
					);

	/**
	 * @brief - login out
	 * @details - login out
	 * 
	 * @param username - username
	 * 
	 * @pre - username must be logged in
	 */
	ACTION logout( const name& username );



	/**
	 * @brief - delete user
	 * @details - delete username
	 * 
	 * @param username - username
	 */
	ACTION deluser( const name& username );

	/**
	 * @brief - add park data
	 * @details - Here, park data is to be added by creating a unique id (timestamp, hash).
	 * 
	 * @param tree_id - tree id 
	 * @param lon - lon 
	 * @param lat - lat 
	 * @param species - species 
	 * @param latin_species - latin species 
	 * @param year_planted - year planted
	 * @param diameter_canopy - diameter_canopy
	 * @param dbh - dbh
	 * @param height - height
	 * @param biomass - biomass
	 * 
	 * @pre - park id to be created externally
	 */
	ACTION addparkdata( 
						uint64_t park_id,
						uint64_t tree_id,
						double lon,
						double lat,
						string species,
						string latin_species,
						uint16_t year_planted,
						float diameter_canopy,
						float dbh,
						float height,
						float biomass
						);


	/**
	 * @brief - delete park tree
	 * @details - delete park tree
	 * 
	 * @param park_id - park id
	 * @param tree_id - tree id
	 * 
	 * @pre - park id exists
	 */
	ACTION delparktree( uint64_t park_id,
						uint64_t tree_id
						);


	/**
	 * @brief - enter/exit park with id
	 * @details - enter/exit park with id
	 * 
	 * @param username - username
	 * @param park_id - park id
	 * @param is_checked_in - loggedin/loggedout
	 * 
	 * @pre - park id exists
	 */
	ACTION entrexitpark( const name& username,
					uint64_t park_id,
					bool is_checked_in 
					);


	// ==================================================================================
	// scope: self
	TABLE profile
	{
		name username;
		string email_id;
		checksum256 password_hash;
		bool is_logged_in;			// (0: loggedout, 1: loggedin)

		auto primary_key() const { return username.value; }
	};

	using profile_index = multi_index<"profile"_n, profile>;

	// ==================================================================================
	// scope: park_id
	TABLE userentry
	{
		name username;
		bool is_checked_in;			// (0: outside, 1: inside)

		auto primary_key() const { return username.value; }
	};

	using userentry_index = multi_index<"userentry"_n, userentry>;

	//-----------------------------------------------------------------------------------
	// scope: park_id (to be created externally)
	TABLE parkinfo
	{
		uint64_t tree_id;
		// uint64_t park_id;
		double lon;
		double lat;
		string species;
		string latin_species;
		uint16_t year_planted;
		float diameter_canopy;
		float dbh;
		float height;
		float biomass;

		auto primary_key() const { return tree_id; }
		// uint64_t by
	};

	using parkinfo_index = multi_index<"parkinfo"_n, parkinfo>;

	//-----------------------------------------------------------------------------------
	// scope: self
	TABLE fund
	{
		name username;
		/*
			[ 
				{ "key": { "symbol": "4,SOV", "contract": "sovmintofeos" }, "value": 30000 }, 
				{ "key": { "symbol": "4,FROG", "contract": "frogfrogcoin" }, "value": 3500000 }, 
				{ "key": { "symbol": "4,PEOS", "contract": "thepeostoken" }, "value": 100000 }, 
				{ "key": { "symbol": "4,KROWN", "contract": "krowndactokn" }, "value": 7169 } 
			]
			
			Here, quantity amount is 30000/10^4 = 3 i.e. asset is "3.0000 SOV"
		*/
		map<extended_symbol, uint64_t> deposit_qty; // map with extended_symbol, uint64_t

		auto primary_key() const { return username.value; }
	};

	using fund_index = multi_index<"fund"_n, fund>;

	// ==================================================================================
	// get the current timestamp
	inline uint32_t now() const {
		return current_time_point().sec_since_epoch();
	}

	/*	
		Here, 2 cases are covered in which the balances map is modified when the row with (owner, balances) exist: 
			- case-1: if the row exists & key is found. i.e. the parsed quantity symbol is found
				- add/sub quantity amount is done by an arithmetic_op (0/1) => (-/+) 
			- case-2: if the row exists & key is NOT found. i.e. the parsed quantity symbol is NOT found 
	*/	
	inline void creatify_balances_map( map<extended_symbol, uint64_t>& m, const asset& qty, 
								bool arithmetic_op, 			// add/sub balance from existing quantity
								const name& token_contract_name ) {
		auto s_it = std::find_if(m.begin(), m.end(), 
							[&](auto& ms) {return ms.first.get_symbol() == qty.symbol;});
		
		if(s_it != m.end()) {		// key found
			if (arithmetic_op == 1)
				s_it->second += qty.amount;
			else if (arithmetic_op == 0)
				s_it->second -= qty.amount;
		}
		else {						// key NOT found
			if (token_contract_name == ""_n)
				m.insert( make_pair(extended_symbol(qty.symbol, get_first_receiver()), qty.amount) );
			else
				m.insert( make_pair(extended_symbol(qty.symbol, capture_contract_in_map(m, qty)), qty.amount) );
		}
	}

	/*	
		Here, 2 cases are covered in which the balances map is checked for <>= than the given quantity, when the row with (owner, balances) exist: 
			- case-1: if the row exists & key is found. i.e. the parsed quantity symbol is found
				- check for >= , else throw message
			- case-2: if the row exists & key is NOT found. i.e. the parsed quantity symbol is NOT found 
				- throw message saying that there is no balances available
	*/	
	inline void compare_amount_in_map( map<extended_symbol, uint64_t> m, const asset& qty ) {
		auto s_it = std::find_if(m.begin(), m.end(), 
							[&](auto& ms) {return ms.first.get_symbol() == qty.symbol;});
		
		if(s_it != m.end()) {		// key found
			check( s_it->second >= qty.amount, "Insufficient balance in from\'s account." );
		}
		else {						// key NOT found
			check( false, "there is no balances available corresponding to the parsed quantity symbol for the given from_id." );
		}
	}

	/*	
		Here, capture the token contract name in which the balances map exists in the row with (owner, balances) exist: 
			- case-1: if the row exists & key is found. i.e. the parsed quantity symbol is found
				- capture the contract ac name from the key
	*/	
	inline name capture_contract_in_map( map<extended_symbol, uint64_t> m, const asset& qty ) {
		name token_contract_ac = ""_n;

		auto s_it = std::find_if(m.begin(), m.end(), 
							[&](auto& ms) {return ms.first.get_symbol() == qty.symbol;});
		
		if(s_it != m.end()) {		// key found
			token_contract_ac = s_it->first.get_contract();
		}
		else {
			check(false, "there is no contract account found with this quantity");
		}

		return token_contract_ac;
	}

/*	bool is_emailid_valid( const string& email_id ) {
	  
	    // Regular expression definition
	    const regex pattern(
	        "(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
	  
	    // Match the string pattern
	    // with regular expression
	    return regex_match(email_id, pattern);
	}
*/

};
