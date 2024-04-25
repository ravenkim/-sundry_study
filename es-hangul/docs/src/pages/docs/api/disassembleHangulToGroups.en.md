---
title: disassembleHangulToGroups
---

# disassembleHangulToGroups

Completely separate a Hangul string into individual characters based on the initial consonant, medial vowel, and final consonant.

Complex consonants like `ㄵ` are split into `['ㄴ', 'ㅈ']`, and complex vowels like `ㅘ` are split into `['ㅗ', 'ㅏ']`.

For detailed examples, please refer to the section below.

```typescript
function disassembleHangulToGroups(
  // The Korean string to be disassembled
  str: string
): string[][];
```

## Examples

```typescript
disassembleHangulToGroups('값'); // [['ㄱ', 'ㅏ', 'ㅂ', 'ㅅ']]
disassembleHangulToGroups('ㅘ'); // [['ㅗ', 'ㅏ']]
disassembleHangulToGroups('ㄵ'); // [['ㄴ', 'ㅈ']]
```
