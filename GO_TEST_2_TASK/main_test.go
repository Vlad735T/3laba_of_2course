package main

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestQueue(t *testing.T) {
	q_fir := new_queue()
	q_sec := new_queue()
	q_thir := new_queue()

	q_fir.push("little")
	q_fir.push("big")
	q_fir.push("lazy")
	q_fir.push("clever")
	q_fir.print()

	assert.True(t, q_sec.is_empty(), "QUEUE is empty!!!")
	assert.False(t, q_fir.is_empty(), "QUEUE is not empty!!!")

	q_sec.push("Volkswagen")
	q_sec.push("Toyota")
	q_sec.push("BMW")
	q_sec.push("Volvo")
	q_sec.print()

	size_fir, err := q_fir.size()
	size_sec, errors := q_sec.size()

	assert.Equal(t, 4, size_fir, "size of q_fir should be 4")
	assert.Equal(t, 4, size_sec, "size of q_sec should be 4")
	assert.NoError(t, err)
	assert.NoError(t, errors)

	del_fir_value := q_fir.pop()
	del_sec_value := q_sec.pop()

	assert.Equal(t, "little", del_fir_value, "The first deleted element should be 'little'")
	assert.Equal(t, "Volkswagen", del_sec_value, "The first deleted element from q_sec should be 'Volkswagen'")

	q_thir.push("Volkswagen")
	q_thir.pop()
}
