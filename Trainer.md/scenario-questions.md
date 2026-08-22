# Scenario-Based Technical Questions

Real-world "what would happen if…" questions common in **F2F technical interviews** (security, networking, product companies). Each entry: scenario → questions → model answer.

---

## How to Use

**Students:** Read scenario, answer aloud in 60 seconds, then check model answer.  
**Trainers:** Pick 2–3 per mock from different sections. See [TRAINER.md](../TRAINER.md).

---

## OS Scenarios

### S1: Two threads increment a shared counter

**Scenario:** Two threads run `count++` on shared variable `count = 0`. Expected 20000, sometimes get less.

**Q:** What goes wrong? How to fix?

**A:** `count++` is not atomic (read-modify-write). Race condition — lost updates. Fix: `mutex` lock around increment, or atomic integer (`std::atomic`, Java `AtomicInteger`).

---

### S2: Process vs thread for web server

**Scenario:** Design handles 10,000 concurrent HTTP requests.

**Q:** Process per request vs thread pool vs async?

**A:** Process per request — too heavy. Thread pool — common, shared memory. Async/event loop (Node, asyncio) — few threads, many connections. Trade-off: CPU-bound → threads/processes; I/O-bound → async.

---

### S3: Deadlock in dining

**Scenario:** Two threads lock mutex A then B; two others lock B then A.

**Q:** Identify problem and prevention.

**A:** Circular wait → deadlock. Prevention: global lock ordering (always A before B), or try-lock with timeout, or banker’s algorithm.

---

### S4: High memory usage, disk thrashing

**Scenario:** System slow, disk LED always on, CPU idle.

**Q:** What is happening?

**A:** Thrashing — more processes than RAM, constant page swapping. Fix: reduce multiprogramming, add RAM, improve locality.

---

### S5: Producer faster than consumer

**Scenario:** Producer fills buffer; consumer slow.

**Q:** What happens without synchronization?

**A:** Buffer overflow or lost data. Use bounded buffer + semaphores (`empty`, `full`, `mutex`) — classic producer-consumer.

---

## DBMS Scenarios

### S6: Bank transfer partial failure

**Scenario:** Transfer ₹1000 A→B. Debit succeeds, crash before credit.

**Q:** How does DB prevent this?

**A:** Transaction with ACID. Wrap in `BEGIN…COMMIT`. On crash before commit → ROLLBACK on recovery. Both or neither.

---

### S7: Two users book last seat

**Scenario:** Concert has 1 seat left; two users click "Book" simultaneously.

**Q:** How to handle?

**A:** Transaction + row lock (`SELECT … FOR UPDATE`) on seat row. Second txn waits or fails. Optimistic locking with version column alternative.

---

### S8: Slow query on large table

**Scenario:** `SELECT * FROM orders WHERE customer_id = 5` takes 30 seconds.

**Q:** First steps to optimize?

**A:** `EXPLAIN` query plan. Add index on `customer_id`. Avoid `SELECT *` if not needed. Check full table scan vs index scan.

---

### S9: DELETE without WHERE

**Scenario:** Engineer runs `DELETE FROM users` without WHERE in production.

**Q:** Prevention and recovery?

**A:** Prevention: read-only replicas for analytics, mandatory code review, backup before migration, soft delete (`deleted_at`). Recovery: restore from backup/PITR (point-in-time recovery).

---

### S10: Read uncommitted isolation

**Scenario:** Transaction A updates salary, not committed. Transaction B reads it.

**Q:** Problem name and fix?

**A:** Dirty read. Fix: raise isolation to Read Committed or higher.

---

## Computer Network Scenarios

### S11: User on public Wi-Fi accesses bank

**Q:** How is data protected?

**A:** HTTPS/TLS encrypts traffic. Attacker sees ciphertext, not credentials. Also verify cert (no MITM). Avoid HTTP sites.

---

### S12: DNS server down

**Scenario:** User cannot open `google.com` but can ping `8.8.8.8`.

**Q:** Diagnosis?

**A:** DNS resolution failing. IP works — network up. Fix: alternate DNS (8.8.8.8), check resolver config, flush DNS cache.

---

### S13: SYN flood attack

**Scenario:** Server receives many SYN packets, few complete handshake.

**Q:** What attack and mitigation?

**A:** SYN flood — exhausts connection table. Mitigate: SYN cookies, rate limiting, firewall rules, CDN/WAF.

---

### S14: Employee bypasses corporate proxy

**Scenario:** User uses mobile hotspot instead of corporate network.

**Q:** Security impact?

**A:** Traffic bypasses SWG/proxy inspection. Policy violation. Endpoint DLP/agent may still apply; CASB for cloud apps. Education + MDM enforcement.

---

### S15: HTTP vs HTTPS on login page

**Q:** Why must login be HTTPS?

**A:** Credentials sent in request body. HTTP = plaintext — MITM can steal. HTTPS encrypts + authenticates server.

---

### S16: CDN value

**Scenario:** Users in India, server in US, slow image load.

**Q:** Solution?

**A:** CDN caches static assets at edge (Mumbai PoP). Lower latency, less origin load. DNS routes to nearest edge.

---

## Security Scenarios

### S17: SQL injection in login form

**Scenario:** Input `' OR '1'='1` logs in without password.

**Q:** Fix?

**A:** Parameterized queries / prepared statements — never concatenate user input into SQL. Input validation secondary.

---

### S18: Stored XSS in comments

**Scenario:** User posts `<script>steal()</script>` in comment; others' browsers run it.

**Q:** Prevention?

**A:** Output encoding/escaping, Content-Security-Policy header, sanitize HTML input. HttpOnly cookies limit cookie theft.

---

### S19: Password database leak

**Scenario:** Attacker gets DB dump with password column.

**Q:** What should have been done?

**A:** Never store plaintext. Salted slow hash (bcrypt, Argon2). Unique salt per user. Consider pepper in app config.

---

### S20: Zero Trust vs traditional VPN

**Q:** Why replace VPN with ZTNA?

**A:** VPN grants broad network access once connected. Zero Trust verifies identity + device + context per application — least privilege, no implicit trust inside network.

---

## Coding / Design Scenarios

### S21: API rate limiting

**Scenario:** Client sends 10,000 requests/sec to your API.

**Q:** Design basic rate limiter.

**A:** Fixed window or token bucket per user/IP. Return 429 Too Many Requests when exceeded. Redis counter common implementation.

---

### S22: Log file too large for memory

**Scenario:** Find most frequent IP in 10 GB log file.

**Q:** Approach?

**A:** Stream line by line — don't load all. Hash map IP → count. If memory limited — external sort, MapReduce, or approximate (Count-Min Sketch).

---

### S23: Cache stampede

**Scenario:** Popular cache key expires; 1000 requests hit DB simultaneously.

**Q:** Mitigation?

**A:** Lock on rebuild, stale-while-revalidate, random TTL jitter, pre-warm cache.

---

## Trainer Quick-Pick Sets

| Set | IDs | Theme |
|-----|-----|-------|
| **Set A** | S6, S11, S17, S1 | Security + concurrency basics |
| **Set B** | S14, S15, S19, S20 | Network security product company |
| **Set C** | S2, S8, S12, S21 | Backend / performance |
| **Set D** | S3, S7, S9, S5 | OS + DBMS depth |

[← TRAINER.md](../TRAINER.md) · [← Index](../README.md)
