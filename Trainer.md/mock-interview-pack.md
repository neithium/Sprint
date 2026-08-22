# Mock Interview Pack — Student Self-Test

Print or open during **solo / peer mock**. One full 45-minute session. Answers in linked files — try first, then check.

---

## Before You Start

- [ ] Timer set to 45 minutes
- [ ] Paper for architecture diagram
- [ ] IDE or blank file for coding
- [ ] No googling until after mock

**Trainer-led mock:** Use [TRAINER.md](../TRAINER.md) instead — interviewer picks questions.

---

## Minute 0–3: Introduction

**Prompt:** "Tell me about yourself in 2 minutes."

**Self-check:**
- [ ] Name, college, branch, year
- [ ] One line on focus (backend / full-stack / etc.)
- [ ] Best project in one sentence
- [ ] Closed with "Happy to take technical questions"

Reference: [interview-tips.md](interview-tips.md)

---

## Minute 3–15: Coding Problem 1 (Easy)

**Problem:** Valid Anagram — Given strings `s` and `t`, return true if `t` is an anagram of `s`.

**Examples:** `s = "anagram", t = "nagaram"` → true

**Self-check after coding:**
- [ ] Stated approach before coding
- [ ] Handled empty strings
- [ ] Said O(n) time, O(1) space (26 letters)

**Solution:** [solutions-python.md](solutions-python.md) #1

---

## Minute 15–27: Coding Problem 2 (Medium)

**Problem:** Longest Substring Without Repeating Characters — Given string `s`, return length of longest substring with all unique characters.

**Example:** `"abcabcbb"` → 3 (`"abc"`)

**Self-check:**
- [ ] Sliding window explained
- [ ] O(n) time stated
- [ ] Walked through example on paper

**Solution:** [solutions-python.md](solutions-python.md) #3

---

## Minute 27–32: SQL (Whiteboard)

**Problem:** Write SQL to find employees who earn more than their manager.

**Tables:** `employees(id, name, salary, manager_id)`

**Self-check:**
- [ ] Used self-join
- [ ] `WHERE e.salary > m.salary`

**Solution:** [dbms-sql.md](dbms-sql.md) — Query #2

---

## Minute 32–40: Fundamentals Rapid-Fire

Answer each in **≤30 seconds** aloud, then score yourself:

| # | Question | Check answer in |
|---|----------|-----------------|
| 1 | Process vs thread? | [TRAINER.md](../TRAINER.md) §3 OS |
| 2 | ACID properties? | [dbms-sql.md](dbms-sql.md) |
| 3 | TCP vs UDP? | [computer-networks.md](computer-networks.md) |
| 4 | Four OOP pillars? | [oop.md](oop.md) |
| 5 | Authentication vs authorization? | [network-security-basics.md](network-security-basics.md) |

**Score:** ___ / 5

---

## Minute 40–45: Project

**Prompts (answer all):**
1. Draw architecture of your best project (boxes + arrows).
2. What was **your** contribution (not team's)?
3. Interviewer picks one resume keyword — explain it simply.

Reference: [projects-resume.md](projects-resume.md)

---

## After Mock — Score Yourself

| Section | Max | Your score |
|---------|-----|------------|
| Intro clarity | 3 | |
| Coding 1 | 3 | |
| Coding 2 | 3 | |
| SQL | 3 | |
| Fundamentals /5 | 3 | |
| Project | 3 | |

**Convert fundamentals:** 5/5 → 3, 3/5 → 2, ≤2/5 → 1

| Total avg | Action |
|-----------|--------|
| ≥ 2.5 | Ready — one more mock |
| 2.0 – 2.4 | Revise weak sections below |
| < 2.0 | Full week plan in [README](../README.md) |

---

## Alternate Mock Sets (Peer Practice)

### Set B — Greedy + Stack focus

| Block | Problem |
|-------|---------|
| Easy | Two Sum |
| Medium | Jump Game |
| SQL | Second highest salary |
| Scenario | [scenario-questions.md](scenario-questions.md) S6, S11 |

### Set C — Trees + DBMS focus

| Block | Problem |
|-------|---------|
| Easy | Max Depth of Binary Tree |
| Medium | Number of Islands |
| SQL | Departments with no employees |
| Scenario | S8, S17 |

### Set D — Security / networking company profile

| Block | Problem |
|-------|---------|
| Easy | Valid Parentheses |
| Medium | Evaluate RPN |
| SQL | GROUP BY + HAVING |
| Fundamentals | 3 CN + 2 Security questions |
| Scenario | [scenario-questions.md](scenario-questions.md) Set B |

---

## 7-Day Self-Mock Schedule

| Day | Mock set | Revise after |
|-----|----------|--------------|
| 1 | Set A (this pack) | strings, dbms join |
| 2 | Set B | greedy, arrays |
| 3 | Set C | trees, graphs |
| 4 | Set D | CN, security |
| 5 | Set A again — timed | weak areas |
| 6 | Peer mock with rubric | [TRAINER.md](../TRAINER.md) |
| 7 | Light revision only | project pitch |

[← Index](../README.md) · [Solutions →](solutions-python.md)
