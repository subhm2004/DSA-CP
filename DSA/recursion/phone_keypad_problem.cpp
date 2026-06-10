/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : phone_keypad_problem.cpp
 * PROBLEM  : Phone Keypad Problem
 * LEETCODE : 17 — Letter Combinations of a Phone Number
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Backtrack letter combinations for phone digits.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

// ════════════════════════════════════════════════════════════════════════════
// PHONE KEYPAD — Digit string se letter combinations
// ────────────────────────────────────────────────────────────────────────────
// Har digit ke corresponding letters (2->abc, 3->def, ...)
// Backtracking: har digit pe ek letter choose, recurse, undo
// Example: "23" -> ["ad","ae","af","bd","be","bf","cd","ce","cf"]
// Note: Is file me abhi sirf header hai — implementation add karni hogi
// ════════════════════════════════════════════════════════════════════════════
