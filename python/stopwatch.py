#!/bin/env/python3
################################################################################
# stopwatch class to support with statement
################################################################################

import sys
import time


class Stopwatch(object):
	"""
	"""
	def __init__(self, fmt = "%.6fs", *ka, **kw):
		super().__init__(*ka, **kw)
		self.fmt = fmt
		self.start() # a default start
		return

	def start(self):
		"""
		record current time as the start timepoint, and reset end time
		"""
		self._start_time = time.time()
		self._end_time = None
		return

	def stop(self):
		"""
		record current time as end time
		"""
		self._end_time = time.time()
		return

	def get_elapsed_time(self):
		"""
		if stop() is already called, return the duration between start and end
		timepoints; otherwise return the duration from start timepoint to
		current time
		"""
		ret = (time.time() if self._end_time is None else self._end_time)\
			- self._start_time
		return ret

	def print_elapsed_time(self, fmt = None, *, file = sys.stderr):
		"""
		print formatted elasped time
		"""
		fmt = (self.fmt if fmt is None else fmt)
		print(fmt % self.get_elapsed_time(), file = file)
		return

	def __enter__(self):
		self.start()
		return self

	def __exit__(self, extype, exvalue, extraceback):
		if extype is None:
			self.print_elapsed_time()
		return
